#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

int pinoServo1 = 3;
int pinoServo2 = 13;
Servo servo1;
Servo servo2;

int led1 = 4;
int led2 = 12;
int trig1 = 7;
int echo1 = 6;
int trig2 = 10;
int echo2 = 9;
int buzzer = 2;

int distanciaEntrada;
int distanciaSaida;
int VagasDisponiveis = 10;

unsigned long tempoAberturaEntrada = 0;
unsigned long tempoAberturaSaida = 0;
unsigned long TEMPO_ABERTURA = 3000;

bool cancelaAbertaEntrada = false;
bool cancelaAbertaSaida = false;
bool carroEntradaProcessado = false;
bool carroSaidaProcessado = false;

// Alerta de proximidade
unsigned long tempoAlertaAnterior = 0;
bool estadoAlerta = false;

// LCD
unsigned long tempoLCDAnterior = 0;
unsigned long intervaloLCD = 500;

void setup() {
  servo1.attach(pinoServo1, 500, 2500);
  servo2.attach(pinoServo2, 500, 2500);
  servo1.write(0);
  servo2.write(0);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(buzzer, OUTPUT);

  lcd_1.begin(16, 2);
  lcd_1.print("Sistema iniciado");
  delay(2000);
  lcd_1.clear();

  Serial.begin(9600);
}

long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH);
  return duracao / 58;
}

void controlarEntrada() {
  if (distanciaEntrada < 50 && !cancelaAbertaEntrada && !carroEntradaProcessado) {
    servo1.write(90);
    tempoAberturaEntrada = millis();
    cancelaAbertaEntrada = true;
    VagasDisponiveis--;
    carroEntradaProcessado = true;
  }
  if (cancelaAbertaEntrada && millis() - tempoAberturaEntrada >= TEMPO_ABERTURA) {
    servo1.write(0);
    cancelaAbertaEntrada = false;
    carroEntradaProcessado = false;
  }
}

void controlarSaida() {
  if (distanciaSaida < 50 && !cancelaAbertaSaida && !carroSaidaProcessado) {
    servo2.write(90);
    tempoAberturaSaida = millis();
    cancelaAbertaSaida = true;
    VagasDisponiveis++;
    carroSaidaProcessado = true;
  }
  if (cancelaAbertaSaida && millis() - tempoAberturaSaida >= TEMPO_ABERTURA) {
    servo2.write(0);
    cancelaAbertaSaida = false;
    carroSaidaProcessado = false;
  }
}

void alertaProximidade() {
  unsigned long agora = millis();
  int intervaloAlerta = 0;

  if (distanciaEntrada < 10) {
    intervaloAlerta = 50;
    tone(buzzer, 3000);
  } else if (distanciaEntrada < 20) {
    intervaloAlerta = 200;
    tone(buzzer, 1500);
  } else {
    digitalWrite(led1, LOW);
    noTone(buzzer);
    return;
  }

  if (agora - tempoAlertaAnterior >= intervaloAlerta) {
    tempoAlertaAnterior = agora;
    estadoAlerta = !estadoAlerta;
    digitalWrite(led1, estadoAlerta ? HIGH : LOW);
  }
}

void atualizarLCD() {
  if (millis() - tempoLCDAnterior >= intervaloLCD) {
    tempoLCDAnterior = millis();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Vagas: ");
    lcd_1.print(VagasDisponiveis);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Dist: ");
    lcd_1.print(distanciaEntrada);
    lcd_1.print("cm   ");
  }
}

void loop() {
  distanciaEntrada = medirDistancia(trig1, echo1);
  distanciaSaida = medirDistancia(trig2, echo2);

  controlarEntrada();
  controlarSaida();
  alertaProximidade();
  atualizarLCD();
}
