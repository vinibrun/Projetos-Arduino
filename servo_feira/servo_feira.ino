
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

void frente(int tempo) {
  direita.write(20);
  esquerda.write(60);
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
  frente(1000);
  gira_dir(300);
  tras(1000);
  gira_esq(2000);
  para(5000);
  }

