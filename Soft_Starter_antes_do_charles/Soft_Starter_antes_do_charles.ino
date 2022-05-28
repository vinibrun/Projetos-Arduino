#define ZeroPin 2
#define OutPin 9
#define imax 7800
#define RelePin 12
/*

  i efetivo: 200 a 8000

  60Hz => T/2 = 8333uS
  detencta zero e conta até 8333uS

  8333 / 50 =

  delay = 8333 / Ta
*/
int i = 3000, y = 0, Ta = 5, BTnum;
bool zero;

void acelerar(long T) {
  for (i = 200; i < imax; i++) {
    delayMicroseconds(T * (i / 70));
  }
  digitalWrite(RelePin, HIGH);
}


void setup() {
  pinMode(ZeroPin, INPUT_PULLUP);
  pinMode(OutPin, OUTPUT);
  pinMode(RelePin, OUTPUT);
  digitalWrite(OutPin, 0);
  digitalWrite(RelePin, 0);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ZeroPin), interrupcao, RISING);
}


// the loop function runs over and over again forever
void interrupcao() {
  if (digitalRead(ZeroPin)) {
    digitalWrite(OutPin, LOW);
    delayMicroseconds(8333 - i);
    digitalWrite(OutPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(OutPin, LOW);
  }
}


void loop() {
  i = 8 * analogRead(A0);
  if (i < 200) acelerar(5);
  Serial.println(i);
  /*  if (i < 8333) {
      i++;
    }
    delayMicroseconds(8333 / Ta);
    Serial.println(i);
  */

  String comando = Serial.readString();
  //Serial.println(comando);
  //String SeFuder = "A";
  bool A = comando.startsWith("A");
  //Serial.println(A);
  //Serial.println(comando);
  if (A) { // acelerar -> enviar AXX, onde XX é o tempo de aceleracao (5 a 50)
    //Serial.println(comando);
    comando.remove(0, 1);
    //Serial.println(comando);
    BTnum = comando.toInt();
    //Serial.println(BTnum);
    if (BTnum) {
      acelerar(BTnum);
      A = 0;
    }
  }

  /*if (comando.startsWith("D")) {// desacelerar -> enviar DXX, onde XX é o tempo de desaceleracao (5 a 50)
    comando.remove(0);
    BTnum = comando.toInt();
    if (BTnum) acelerar(BTnum);
  }
  // i = 8 * analogRead(A0);*/
}










