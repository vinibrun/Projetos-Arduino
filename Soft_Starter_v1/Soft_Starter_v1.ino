#define ZeroPin 2
#define OutPin 11
#define RelePin 10
#define EmergenciaPin 9
#define IPin A0

/*



  60Hz => T/2 = 8333uS
  detencta zero e conta até 8333uS

  8333 / 50 =


*/
int i = 0, y = 0, Taceleracao = 5, Tdesaceleracao = 5, INominal = 500, I = 0, X = 1, Y = 1; // X e Y sao os multiplicadores da corrente nominal (X/Y)
bool zero, EMERGENCIA = 0, ligado = 0, acelerando = 0, desacelerando = 0, SOBRECORRENTE = 0;
String comando;

void envia_bt() { // envia os dados pela porta serial (por enquanto, debug no pc)
  Serial.print("I = ");
  Serial.print(I);
  Serial.print("  INominal = ");
  Serial.print(INominal);
  Serial.print("  Taceleracao = ");
  Serial.print(Taceleracao);
  Serial.print("  Tdesaceleracao = ");
  Serial.print(Tdesaceleracao);
  Serial.print("  EMRGENCIA = ");
  Serial.print(EMERGENCIA);
  Serial.print("  i = ");
  Serial.println(i);
}

void setup() {
  pinMode(ZeroPin, INPUT);
  pinMode(EmergenciaPin, INPUT);
  pinMode(OutPin, OUTPUT);
  pinMode(RelePin, OUTPUT);
  pinMode(IPin, INPUT);
  digitalWrite(OutPin, 0);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ZeroPin), interrupcao, RISING);
}


// the loop function runs over and over again forever
void interrupcao() {
  if (ligado || desacelerando) {
    digitalWrite(OutPin, LOW);
    delayMicroseconds(8333 - i);
    digitalWrite(OutPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(OutPin, LOW);
  }
  I = analogRead(IPin);
}


void loop() {
  if (comando.startsWith("I")) {
    comando.remove(0);
    INominal = (comando.toInt() * X) / Y;
  }

  if (comando.startsWith("A")) {
    comando.remove(0);
    Taceleracao = comando.toInt();
  }


  if (comando.startsWith("D")) {
    comando.remove(0);
    Tdesaceleracao = comando.toInt();
  }



  comando = Serial.readString();
  if (comando == "acelerar") {
    acelerando = 1;
    i = 8333;
  }

  if (i == 0) acelerando = 0;

  if (comando == "desligar") {
    ligado = 0;
  }

  if (comando == "ligar") {
    ligado = 1;
  }

  if (i >= 8333) desacelerando = 0;

  if (comando == "emergencia") EMERGENCIA = 1;

  if (acelerando && I < 1, 5 * INominal) {
    i--;
    delayMicroseconds(8333 / Taceleracao);
  }

  if (desacelerando) {
    i++;
    delayMicroseconds(8333 / Tdesaceleracao);
  }

  I = analogRead(IPin);
  if (digitalRead(EmergenciaPin))EMERGENCIA = 1;
  if (comando == "emergencia") EMERGENCIA = 1;
  if ( I > 2 * INominal) SOBRECORRENTE = 1;
  if (I == 0) EMERGENCIA = 0;
  if (EMERGENCIA || SOBRECORRENTE || !ligado) {
    acelerando = 0;
    desacelerando = 1;
  }
  envia_bt();
}



