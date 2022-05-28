#define ZeroPin 2
#define OutPin 9
#define imax 7800
#define imin 350
#define RelePin 12
#define BuzzerPin 7
/*

  i efetivo: imin a 8000

  60Hz => T/2 = 8333uS
  detencta zero e conta até 8333uS

  8333 / 50 =

  delay = 8333 / Ta
*/
int i = imin, y = 0, Ta = 5, BTnum, corrente[500], j = 0, Inominal = 230, I150 = 250, I200 = 300, Iinst, Imin = 30;
bool zero, ligado = 0, sobrecorrente = 0;

//função de aceleração

void acelerar(long T) {
  digitalWrite(BuzzerPin, LOW);
  j = 0;
  int soma = 0;
  int soma_ = 0;
  Serial.println("ligar");
  for (i = imin; i < imax; i++) {

    if (i < imin + 100) {
      delayMicroseconds(T * 20);
      I150 = 230;
    }
    else {
      delayMicroseconds(T * (i / 70));
      I150 = 260;
    }
    if (!(i % 5)) {

      soma += analogRead(A0);
      if (!(i % 80)) {

        if (soma < 2 * soma_ && soma_ < 2 * soma) {
          Iinst =  soma / 16;
          corrente[j] = Iinst;
          soma_ = soma;
          soma = 0;
          j++;
        }
      }
    }
    if (Iinst > I150)i--;
    if (Iinst > I200) {
      sobrecorrente = 1;
      i = imax;
    }
  }
  if (sobrecorrente) {
    i = imin;
  }
  else {
    digitalWrite(RelePin, HIGH);
  }
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
  Serial.println("desligar");
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
    if (corrente[j] > I150)i--;
    if (corrente[j] > I200) {
      sobrecorrente = 1;
      i = imin;
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
  if (digitalRead(ZeroPin) && ligado && !sobrecorrente) {
    digitalWrite(OutPin, LOW);
    delayMicroseconds(8333 - i);
    digitalWrite(OutPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(OutPin, LOW);
  }
}


void loop() {
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
  if (D) { // desacelerar -> enviar DXX, onde XX é o tempo de desaceleracao (5 a 50)
    ligado = 1;
    comando.remove(0, 1);
    BTnum = comando.toInt();
    if (BTnum) {
      desacelerar(BTnum);
      D = 0;
    }
  }
  bool S = comando == ("S");
  if (S) {
    sobrecorrente = 0;
  }
  Iinst = analogRead(A0);
  if (Iinst > I200)sobrecorrente = 1;
  if (Iinst < Imin)digitalWrite(RelePin, LOW);
  if (sobrecorrente) {
    Serial.println("SOBRECORRENTE");
    digitalWrite(RelePin, LOW);
    i = imin;
  }
  i = 0;
}










