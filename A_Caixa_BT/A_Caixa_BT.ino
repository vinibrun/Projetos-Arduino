/* * * * * * * * * * * * * * * * * A Caixa * * * * * * * * * * * * * * * * *
        A Caixa é uma plataforma de prototipapgem que facilita a introdução
    ao Arduino por possuir sensores, chaves, atuador e senalizações já
    conectadas à placa. Os respectivos pinos estão indicados na Caixa.
        Facilita a programação e teste de algoritmos por possuir tais
    elementos integrados ao Arduino, evitando, assim, erros na montagem
    e problemas com mal contato.
                                                  Vinícius Brun Kriesang
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * The Box * * * * * * * * * * * * * * * * *
        The Box is a developing plataform that provides the necessary to
    start learning Arduino, including sensors, switches, motor and Leds
    ready-to-use. The pins of each component is described at The Box.
        Makes programming and algorytim teste easyer by offering those
    components integrated to Arduino, avoiding problems with schematic.    *
                                                  Vinícius Brun Kriesang
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * PT-BR * * * * * * * * * * * * * * * * *
        Esta é a versão brasileira do código. A versão em inglês pode ser
    encontrada em: LINK
        This is the brasilian version of the code. The english version can *
    be found at: LINK
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * Facebook * * Twitter * * Youtube * * * * * * * * * *
        Para mais projetos, códigos e algoritmos, siga-me no Facebook, no
    Twitter e no Youtube.
        For more projects, codes and algorithims, follow me on Facebook,
    Twitter and Youtube.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */





/* * * * * Declaração de pinos * * Pin defining * * * * */
// Ponte H conectada aos pinos 5 e 6, movimenta o motor nos dois sentidos com controle de velocidade
#define LedInternoPin 3
#define MotorPinA 5     // Ponte H conectada aos pinos 5 e 6, movimenta o motor nos dois sentidos com controle de velocidade
#define MotorPinB 6
#define ChaveAPin 7     // Chaves A e B são duas chaves independentes conectadas  
#define ChaveBPin 8
#define C1Pin 9         // C1 e C2 são os dois terminais de uma chave de 3 posições. O pino central é alimentado e a chave seleciona C1 ou C2
#define C2Pin 10
#define LedPin1 11      // Leds 1, 2 e 3 conectados em saídas digitais
#define LedPin2 12
#define LedPin3 13
#define LdrPin A0       // Ldr para leitura de intensidade de iluminação ambiente
#define ChuvaPin A1     // Sensor de chuva, identifica água e é sensível ao toque
#define SExternoPin A2  // Entrada para sensor externo 


/* * * * * Declaração de variáveis de controle * * Control variables defining * * * * */
int MotorA = 0; // Valores escritos nos pinos do motor (0 a 255)
int MotorB = 0;
bool Led1 = 0;  // Valores escritos nos Leds (0 ou 1);
bool Led2 = 0;
bool Led3 = 0;
int A;//digitalRead(ChaveAPin);  // Lê as chaves
int B;// = digitalRead(ChaveBPin);
bool C1;// = digitalRead(C1Pin);
bool C2;// = digitalRead(C2Pin);
int ValorChuva;// = analogRead(ChuvaPin); // Lê os sensores analógicos
int ValorLdr;// = analogRead(LdrPin);
int ValorSExterno;// = analogRead(SExternoPin);

String comandos[5] = {
  /* 01 */  "*azul#",
  /* 02 */  "*azul claro#",
  /* 03 */  "*azul escuro#"
};


  /* * * * * Função de atualização dos pinos * * Pin update funccion * * * * */
  void atualiza() { // Lê e escreve nos pinos de entrada e saída
    analogWrite(MotorPinA, MotorA);   // Escreve nos pinos do motor
    analogWrite(MotorPinB, MotorB);
    A = digitalRead(ChaveAPin);  // Lê as chaves
    B = digitalRead(ChaveBPin);
    C1 = digitalRead(C1Pin);
    C2 = digitalRead(C2Pin);
    digitalWrite(LedPin1, Led1);      // Escreve nos pinos dos Leds
    digitalWrite(LedPin2, Led2);
    digitalWrite(LedPin3, Led3);
    ValorChuva = analogRead(ChuvaPin); // Lê os sensores analógicos
    ValorLdr = analogRead(LdrPin);
    ValorSExterno = analogRead(SExternoPin);
  }

  void envia_serial() {
    Serial.print(ValorChuva);
    Serial.print("  ");
    Serial.print(ValorLdr);
    Serial.print("  ");
    Serial.print(ValorSExterno);
    Serial.print("  ");
    Serial.print(A);
    Serial.print("  ");
    Serial.print(B);
    Serial.print("  ");
    Serial.print(C1);
    Serial.print("  ");
    Serial.print(C2);
    Serial.println("  ");
  }


  void setup() {
    /* * * * * Declaração de pinos de entrada e saída * * Input/Output defining * * * * */
    pinMode(MotorPinA,   OUTPUT);
    pinMode(MotorPinB,   OUTPUT);
    pinMode(ChaveAPin,   INPUT);
    pinMode(ChaveBPin,   INPUT);
    pinMode(C1Pin,       INPUT);
    pinMode(2,   OUTPUT);
    pinMode(3,   OUTPUT);
    pinMode(4,       OUTPUT);
    pinMode(C2Pin,       INPUT);
    pinMode(LedPin1,     OUTPUT);
    pinMode(LedPin2,     OUTPUT);
    pinMode(LedPin3,     OUTPUT);
    pinMode(LdrPin,      INPUT);
    pinMode(ChuvaPin,    INPUT);
    pinMode(SExternoPin, INPUT);

    Serial.begin(9600);
  }

  void loop() { // Espaço para algoritmo
    atualiza();
    envia_serial();
    delay(100);


    if (ValorChuva > 900) Led1 = 1; else Led1 = 0;
    if (ValorChuva < 500) Led2 = 1; else Led2 = 0;
    MotorA = 250 * A;
    MotorB = 150 * B;
    if (ValorLdr > 900) Led3 = 1; else Led3 = 0;
    digitalWrite(3, HIGH);
    comando = Serial.readString();
    if (comando != ""){
    comando.toLowerCase();
    Serial.println(comando);
    i = 0;
    while (i < 6 && comando != caomandos[i])
      i++;
    }
  }
