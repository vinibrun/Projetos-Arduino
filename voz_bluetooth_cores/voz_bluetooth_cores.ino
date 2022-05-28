
#define Rout  9
#define Gout  10
#define Bout  11
#define Sin 7 // switch in

int R = 0, G = 0, B = 0, atual = 0, i;
boolean cont = 0, mudanca;
String comando;

//**************************** MATRIZ DE CORES (NOMES)*******************
String Cores[25] = {
  /* 01 */  "*azul#",
  /* 02 */  "*azul claro#",
  /* 03 */  "*azul escuro#",
  /* 04 */  "*amarelo#",
  /* 05 */  "*amarelo claro#",
  /* 06 */  "*amarelo escuro#",
  /* 07 */  "*branco#",
  /* 08 */  "*cinza#",
  /* 09 */  "*laranja#",
  /* 10 */  "*laranja claro#",
  /* 11 */  "*laranja escuro#",
  /* 12 */  "*roxo#",
  /* 13 */  "*verde#",
  /* 14 */  "*verde claro#",
  /* 15 */  "*verde escuro#",
  /* 16 */  "*vermelho#",
  /* 17 */  "*vermelho claro#",
  /* 18 */  "*vermelho escuro#",
  /* 19 */  "*violetta#",
  /* 20 */  "*ciano#",
  /* 21 */  "*rosa#",
  /* 22 */  "*rosa claro#",
  /* 23 */  "*rosa escuro#",
  /* 24 */  "*prata#",
  /* 25 */  "*dourado#",
  //EASTER EGGS
};
//**************************** MATRIZ DE CORES (RGB)*******************
int cores[25][3]  = {
  /* 01 */  000, 000, 200,
  /* 02 */  000, 000, 255,
  /* 03 */  000, 000, 139,
  /* 04 */  255, 80, 000,
  /* 05 */  255, 255, 200,
  /* 06 */  218, 165, 32,
  /* 07 */  255, 255, 255,
  /* 08 */  128, 128, 128,
  /* 09 */  255, 55, 000,
  /* 10 */  255, 180, 50,
  /* 11 */  255, 185, 15,
  /* 12 */  128, 000, 128,
  /* 13 */  000, 200, 000,
  /* 14 */  000, 255, 000,
  /* 15 */  000, 128, 000,
  /* 16 */  255, 000, 000,
  /* 17 */  255, 100, 70,
  /* 18 */  139, 000, 000,
  /* 19 */  128, 43, 226,
  /* 20 */  000, 255, 255,
  /* 21 */  255, 20, 147,
  /* 22 */  255, 105, 180,
  /* 23 */  200, 20, 133,
  /* 24 */  192, 192, 192,
  /* 25 */  000, 000, 000,
  //EASTER EGGS
};
//*************************************

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
  comando.toLowerCase();
  Serial.println(comando);
  i = 0;
  while (i < 25 && comando != Cores[i])
    i++;

  R = cores[i][0];
  G = cores[i][1];
  B = cores[i][2];
  delay(150);
  printaLed(R, G, B);
}

