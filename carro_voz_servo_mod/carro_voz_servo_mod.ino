
#include <Servo.h>

#define SDpin 10
#define SEpin 11
#define Buzpin 3

Servo direita;
Servo esquerda;
int D = 0, E = 0, atual = 0, i;
boolean cont = 0, mudanca;
String comando;
bool modo = 0, bug = 0;

String Comandos[8] = {
  /* 1 */  "*frente#",
  /* 2 */  "*trás#",
  /* 3 */  "*esquerda#",
  /* 4 */  "*direita#",
  /* 5 */  "*para#",
  /* 6 */  "*mudar modo#",
  /* 7 */  "*bug#",
  /* 8 */  "*bug#"
};

int Movimentos[5][3] {
  /* 1 */  0, 0, 50,
  /* 2 */  180, 180, 50,
  /* 3 */  0, 180, 50,
  /* 4 */  180, 0, 50,
  /* 5 */  90, 90, 300
};

void frente(int tempo) {
  direita.write(0);
  esquerda.write(0);
  delay(tempo);
}
void tras(int tempo) {
  direita.write(180);
  esquerda.write(180);
  delay(tempo);
}
void gira_esq(int tempo) {
  direita.write(180);
  esquerda.write(0);
  delay(tempo);
}
void gira_dir(int tempo) {
  direita.write(0);
  esquerda.write(180);
  delay(tempo);
}
void para(int tempo) {
  direita.write(90);
  esquerda.write(90);
  delay(tempo);
}

void anda(int dir, int esq, int tempo) {
  direita.write(dir);
  if (esq == 180)esq = 140; //correção de velocidade
  if (esq == 0)esq = 60; //correção de velocidade
  
  esquerda.write(esq);
  delay(tempo);
  Serial.print(dir);
  Serial.print(esq);
}



void setup() {
  direita.attach(SDpin);
  esquerda.attach(SEpin);
  pinMode(Buzpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  do {
    comando = Serial.readString();
  } while (comando == "");
  comando.toLowerCase();
  Serial.println(comando);

  i = 0;
  while (i < 7 && comando != Comandos[i]) {
    i++;
  }

  if (i == 6) modo = !modo;
  if (i > 6) bug = 1;
  else {
    anda(Movimentos[i][0], Movimentos[i][1], Movimentos[i][2]);
    //if (!modo) para(50);
  }

  if (bug) {
    digitalWrite(Buzpin, HIGH);
    delay(300);
    digitalWrite(Buzpin, LOW);
    bug = 0;
  }
  Serial.print(i);
}

