
#include <Servo.h>

#define Rout  9
#define Gout  10
#define Bout  11
#define Sin 7 // switch in

Servo direita;
Servo esquerda; 
int D = 0, E = 0, atual = 0, i;
boolean cont = 0, mudanca;
String comando;

//**************************** MATRIZ DE CORES (NOMES)*******************
String Comandos[5] = {
  /* 01 */  "*frente#",
  /* 02 */  "*trás#",
  /* 03 */  "*direita#",
  /* 04 */  "*esquerda#",
  /* 05 */  "*para#"
};
//**************************** MATRIZ DE CORES (RGB)*******************
int velocidades[5][2]  = {
  /* 01 */  000, 000,
  /* 02 */  180, 180,
  /* 03 */  180, 000,
  /* 04 */  000, 180,
            90 , 90
};
//*************************************

void anda(int dir, int esq) {
  direita.write(dir);                  // sets the servo position according to the scaled value
  esquerda.write(esq);                  // sets the servo position according to the scaled value
}

void setup() {
    direita.attach(9);  // attaches the servo on pin 9 to the servo object
    esquerda.attach(10);  // attaches the servo on pin 9 to the servo object
    Serial.begin(9600);
}

void loop() {
  do {
    comando = Serial.readString();
  } while (comando == "");
  comando.toLowerCase();
  Serial.println(comando);
  i = 0;
  while (i < 4 && comando != Comandos[i])
    i++;

  D = velocidades[i][0];
  E = velocidades[i][1];
  anda(D, E);
  delay(500);
  anda(90,90);  
}

