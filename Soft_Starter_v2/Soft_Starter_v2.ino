#define ZeroPin 2
#define OutPin 9
#define imax 7700
#define RelePin 7
/*



  60Hz => T/2 = 8333uS
  detencta zero e conta até 8333uS

  8333 / 50 =

  delay = 8333 / Ta
*/
int i = 7700, y = 0, Ta = 5, BTnum; // imax = 7700
bool zero, eiro = 1;

void setup() {
  pinMode(ZeroPin, INPUT_PULLUP);
  pinMode(OutPin, OUTPUT);
  pinMode(RelePin, OUTPUT);
  digitalWrite(OutPin, 0);
  digitalWrite(RelePin, 0);
  Serial.begin(9600);
}


// the loop function runs over and over again forever
bool interrupcao(int Delay) {
  if (eiro) {
    eiro = 0;
    digitalWrite(OutPin, LOW);
    delayMicroseconds(8333 - Delay);
    digitalWrite(OutPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(OutPin, LOW);
    eiro = 1;
    return 1;
  }
}

void acelerar(long T) {
  T *= 1000;
  i = 0;
  while (i < imax) {
    if (digitalRead(ZeroPin)) {
      int j;
      for(j=0;j<100;j++)
      interrupcao(i);
      i += 100;

    }
  }
  digitalWrite(RelePin, HIGH);
}

void desacelerar(int T) {
  T *= 1000000;
  digitalWrite(RelePin, LOW);
  for (i = imax; i > 0; i--) {
    while (!digitalRead(ZeroPin));
    interrupcao(0);
    delayMicroseconds((T / imax) - 8333);
  }
}

void loop() {
  String comando = Serial.readString();
  Serial.println(comando);
  String SeFuder = "A";
  bool A = comando.startsWith(SeFuder);
  Serial.println(A);
  Serial.println(comando);
  if (A) { // acelerar -> enviar AXX, onde XX é o tempo de aceleracao (5 a 50)
    Serial.println(comando);
    comando.remove(0, 1);
    Serial.println(comando);
    BTnum = comando.toInt();
    Serial.println(BTnum);
    if (BTnum) {
      acelerar(BTnum);
      A = 0;
    }
  }

  if (comando.startsWith("D")) {// desacelerar -> enviar DXX, onde XX é o tempo de desaceleracao (5 a 50)
    comando.remove(0);
    BTnum = comando.toInt();
    if (BTnum) acelerar(BTnum);
  }
  // i = 8 * analogRead(A0);
}






