
#define Rout  9
#define Gout  10
#define Bout  11
#define Sin 7 // switch in

int R = 0, G = 0, B = 0, atual = 0;
boolean cont = 0, mudanca, ligado = 0;
String comando;

void printaLed(int Red, int Green, int Blue) {
  analogWrite(Rout, Red);
  analogWrite(Gout, Green);
  analogWrite(Bout, Blue);
}

void setup() {
  pinMode(Rout, OUTPUT);
  pinMode(Gout, OUTPUT);
  pinMode(Bout, OUTPUT);
  pinMode(Sin, INPUT);

  Serial.begin(9600);
}

void loop() {
  do {
    comando = Serial.readString();
  } while (comando == "");
  if (comando == "azul") {
    digitalWrite(Rout, LOW);
    digitalWrite(Gout, LOW);
    digitalWrite(Bout, HIGH);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "verde") {
    digitalWrite(Rout, LOW);
    digitalWrite(Gout, HIGH);
    digitalWrite(Bout, LOW);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "ciano") {
    digitalWrite(Rout, LOW);
    digitalWrite(Gout, HIGH);
    digitalWrite(Bout, HIGH);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "vermelho") {
    digitalWrite(Rout, HIGH);
    digitalWrite(Gout, LOW);
    digitalWrite(Bout, LOW);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "roxo") {
    digitalWrite(Rout, HIGH);
    digitalWrite(Gout, LOW);
    digitalWrite(Bout, HIGH);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "marrom") {
    digitalWrite(Rout, HIGH);
    digitalWrite(Gout, HIGH);
    digitalWrite(Bout, LOW);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "branco") {
    digitalWrite(Rout, HIGH);
    digitalWrite(Gout, HIGH);
    digitalWrite(Bout, HIGH);
    Serial.println ("A cor atual e:");
    Serial.println (comando);
  }
  if (comando == "d") {
    digitalWrite(Rout, LOW);
    digitalWrite(Gout, LOW);
    digitalWrite(Bout, LOW);
  }
  delay(200);

  /*
    Serial.print("R: ");
    Serial.print(R);
    Serial.print(" G: ");
    Serial.print(G);
    Serial.print(" B: ");
    Serial.println(B);
  */
}

