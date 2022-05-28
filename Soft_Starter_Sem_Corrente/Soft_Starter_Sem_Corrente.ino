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
int valorPot, i = 0, y = 0, Taceleracao = 5, Tdesaceleracao = 5, INominal = 500;
bool zero, EMERGENCIA = 0;
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
  digitalWrite(OutPin, LOW);
  delayMicroseconds(8333 - i);
  digitalWrite(OutPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(OutPin, LOW);
}

void loop() {
  comando = Serial.readString();

  if (comando == "acelerar") {
    acelerando = 1;
    i = 8333;
  }

  if (i == 0) acelerando = 0;

  if (comando == "desacelerar") {
    desacelerando = 1;
    i <= 0;
  }

  if (i >= 8333) desacelerando = 0;

  if (comando == "emergencia") EMERGENCIA = 1;

  if (acelerando && corrente < 1, 5 * INominal) {
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
  if (EMERGENCIA || SOBRECORRENTE) {
    acelerando = 0;
    desacelerando = 1;
  }
}
