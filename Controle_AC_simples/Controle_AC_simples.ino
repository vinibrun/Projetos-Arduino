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
void interrupcao() {
  if (eiro) {
    eiro = 0;
    digitalWrite(OutPin, LOW);
    delayMicroseconds(8333 - i);
    digitalWrite(OutPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(OutPin, LOW);
    eiro = 1;
  }
}

void acelerar(int T) {
  T *= 1000000;
  for (i = 0; i < imax; i++) {
    while (!digitalRead(ZeroPin));
    interrupcao();
    delayMicroseconds((T / imax) - 8333);
  }
  digitalWrite(RelePin, HIGH);
}

void desacelerar(int T) {
  T *= 1000000;
  digitalWrite(RelePin, LOW);
  for (i = imax; i > 0; i--) {
    while (!digitalRead(ZeroPin));
    interrupcao();
    delayMicroseconds((T / imax) - 8333);
  }
}

void loop() {
  String comando = Serial.readString();

  if (comando.startsWith("A")) { // acelerar -> enviar AXX, onde XX é o tempo de aceleracao (5 a 50)
    comando.remove(0);
    BTnum = comando.toInt();
    if (BTnum) acelerar(BTnum);
  }

  if (comando.startsWith("D")) {// desacelerar -> enviar DXX, onde XX é o tempo de desaceleracao (5 a 50)
    comando.remove(0);
    BTnum = comando.toInt();
    if (BTnum) acelerar(BTnum);
  }
  // i = 8 * analogRead(A0);
}






