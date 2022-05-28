#define ZeroPin 2
#define OutPin 9
#define imax 7800
#define imin 300
#define RelePin 12
#define BuzzerPin 7
/*

  i efetivo: imin a 8000

  60Hz => T/2 = 8333uS
  detencta zero e conta até 8333uS

  8333 / 50 =

  delay = 8333 / Ta
*/
int i = imin, y = 0, Ta = 10, Td = 10, BTnum;
bool zero, ligado = 0;

//função de aceleração

void acelerar(long T) {
  digitalWrite(BuzzerPin, LOW);
  for (i = imin; i < imax; i++) {
    delayMicroseconds(T * (i / 70));
  }
  digitalWrite(RelePin, HIGH);
  digitalWrite(BuzzerPin, HIGH);
  ligado = 0;
}

//função de desaceleração

void desacelerar(long T) {
  digitalWrite(BuzzerPin, LOW);
  i = imax;
  digitalWrite(RelePin, LOW);
  for (i = imax; i > imin; i--) {
    delayMicroseconds(T * (i / 70));
  }
  digitalWrite(BuzzerPin, HIGH);
  ligado = 0;
}

void setup() {
  pinMode(ZeroPin, INPUT_PULLUP);
  pinMode(OutPin, OUTPUT);
  pinMode(RelePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, HIGH);
  digitalWrite(OutPin, 0);
  digitalWrite(RelePin, 0);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ZeroPin), interrupcao, RISING);
}


// the loop function runs over and over again forever
void interrupcao() {
  if (digitalRead(ZeroPin) && ligado) {
    digitalWrite(OutPin, LOW);
    delayMicroseconds(8333 - i);
    digitalWrite(OutPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(OutPin, LOW);
  }
}


void loop() {
  i = imin;
  //configurações de aceleração
  String comando;
  do {
    comando = Serial.readString();
  } while (comando == "");
  if (comando == "S") acelerar(Ta);
  if (comando == "R") desacelerar(Td);
  bool A = comando.startsWith("A");
  if (A) { // acelerar -> enviar AXX, onde XX é o tempo de aceleracao (5 a 50)
    ligado = 1;
    comando.remove(0, 1);
    BTnum = comando.toInt();
    if (5 <= BTnum && BTnum <= 50) {
      Ta = BTnum;
    }
    else Serial.print("Tempo inválido");
    A = 0;
  }

  //configurações de desaceleração
  bool D = comando.startsWith("D");
  if (D) { // desacelerar -> enviar AXX, onde XX é o tempo de desaceleracao (5 a 50)
    ligado = 1;
    comando.remove(0, 1);
    BTnum = comando.toInt();
    if (5 <= BTnum && BTnum <= 50) {
      Td = BTnum;
    }
    else Serial.print("Tempo inválido");
    D = 0;
  }
  Serial.print("Tempo de aceleracao: ");
  Serial.print(Ta);
  Serial.print("Tempo de desaceleracao: ");
  Serial.print(Td);
}










