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
int i = imin, y = 0, Ta = 5, BTnum, corrente[500], j = 0;
bool zero, ligado = 0;

//função de aceleração

void acelerar(long T) {
  digitalWrite(BuzzerPin, LOW);
  j = 0;
  int soma;
  for (i = imin; i < imax; i++) {
    delayMicroseconds(T * (i / 70));
    if (!(i % 5)) {
      soma += analogRead(A0);
      if (!(i % 80)) {
        corrente[j] = soma / 16;
        soma = 0;
        j++;
      }
    }
  }
  digitalWrite(RelePin, HIGH);
  Serial.println("A");
  for (j = 0; j < 500; j++)
    if (corrente[j])Serial.println(corrente[j]);
  digitalWrite(BuzzerPin, HIGH);
  ligado = 0;
}

//função de desaceleração

void desacelerar(long T) {
  digitalWrite(BuzzerPin, LOW);
  i = imax;
  j = 0;
  int soma = 0;
  digitalWrite(RelePin, LOW);
  for (i = imax; i > imin; i--) {
    delayMicroseconds(T * (i / 70));
    if (!(i % 5)) {
      soma += analogRead(A0);
      if (!(i % 80)) {
        corrente[j] = soma / 16;
        soma = 0;
        j++;
      }
    }
  }
  digitalWrite(BuzzerPin, HIGH);
  ligado = 0;
  Serial.println("D");
  for (j = 0; j < 500; j++)
    if (corrente[j])Serial.println(corrente[j]);
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
  String comando = Serial.readString();
  bool A = comando.startsWith("A");
  if (A) { // acelerar -> enviar AXX, onde XX é o tempo de aceleracao (5 a 50)
    ligado = 1;
    comando.remove(0, 1);
    BTnum = comando.toInt();
    if (BTnum) {
      acelerar(BTnum);
      A = 0;
    }
  }

  //configurações de desaceleração
  bool D = comando.startsWith("D");
  if (D) { // desacelerar -> enviar AXX, onde XX é o tempo de desaceleracao (5 a 50)
    ligado = 1;
    comando.remove(0, 1);
    BTnum = comando.toInt();
    if (BTnum) {
      desacelerar(BTnum);
      D = 0;
    }
  }

}










