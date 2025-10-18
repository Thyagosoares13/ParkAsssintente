# ParkAsssintente

Rafeel yuri, Samuel, Thyago Soares



 Pensamento Lógico
No início do projeto, Nos adotamos  uma abordagem estratégica: criaram uma estrutura básica do código para entender o funcionamento geral do sistema. Essa etapa foi essencial para visualizar o fluxo de funcionamento do estacionamento inteligente — desde a detecção de veículos até a abertura e fechamento das cancelas. Essa base serviu como um guia para as próximas etapas, permitindo que o grupo evoluísse o código de forma organizada e com propósito.

 Montagem do Circuito
A montagem do circuito foi feita com base em componentes prontos disponíveis no Tinkercad, como o display LCD I2C e o micro servo motor. Esses elementos foram integrados ao projeto conforme a lógica definida anteriormente. O uso de modelos prontos facilitou a conexão dos pinos e a visualização do funcionamento do sistema, garantindo que a parte física estivesse alinhada com o que o código esperava controlar.

Construção do Código
A lógica do código foi construída de forma incremental. nos começamos com funcionalidades simples, como medir a distância com sensores ultrassônicos, e foram adicionando complexidade. Com o apoio de vídeos e ferramentas de IA, conseguiram implementar:
- Controle de cancelas com servo motores, acionadas quando um carro se aproxima.
- Sistema de alerta sonoro e visual, com buzzer e LED piscando em diferentes frequências conforme a proximidade do veículo.
- Contagem de vagas disponíveis, utilizando dois sensores (entrada e saída) para atualizar o número de vagas em tempo real.
- Exibição das informações no display LCD, com atualização periódica usando millis() para evitar travamentos no sistema.
Além disso, o uso de técnicas como controle não-bloqueante com millis() e máquina de estados permitiu que o sistema executasse múltiplas tarefas simultaneamente, como manter a cancela aberta por um tempo determinado enquanto o alerta de proximidade continua funcionando.

https://www.tinkercad.com/things/isbUV96vyhM-park-asssitente/editel



