
#define Rout  9
#define Gout  10
#define Bout  11
#define Sin 7 // switch in

int R = 0, G = 0, B = 0, atual = 0, i;
boolean cont = 0, mudanca;
String comando;

//**************************** MATRIZ DE CORES (NOMES)*******************
String Cores[45] = {
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
  /* 26 */  "*a meca é rei#",
  /* 27 */  "*penta#",
  /* 28 */  "*química eu te amo#",
  /* 29 */  "*abaixem a voz#",
  /* 30 */  "*trio trio#",
  /* 31 */  "*tnt#",
  /* 32 */  "*máfia da graxa#",
  /* 33 */  "*trio eletro#",
  /* 34 */  "*atropelando#",
  /* 35 */  "*heim gato#",
  /* 36 */  "*arduino maior que pic#",
  /* 37 */  "*brun lindo#",
  /* 38 */  "*kopper viado#",
  /* 39 */  "*tro#",
  /* 40 */  "*inverno verde#",
  /* 41 */  "*vai safadão#",
  /* 42 */  "*isso não é um ovo de páscoa#",
  /* 43 */  "*opa é seis#",
  /* 44 */  "*é campeão#",
  /* 45 */  "*desligar#"
};
//**************************** MATRIZ DE CORES (RGB)*******************
int cores[45][3]  = {
  /* 01 */  000, 000, 200,
  /* 02 */  000, 000, 255,
  /* 03 */  000, 000, 139,
  /* 04 */  255, 255, 000,
  /* 05 */  255, 255, 200,
  /* 06 */  218, 165, 32,
  /* 07 */  255, 255, 255,
  /* 08 */  128, 128, 128,
  /* 09 */  255, 165, 000,
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
  /* 25 */  255, 215, 000,
  //EASTER EGGS
  /* 26 */  255, 165, 10,
  /* 27 */  20, 205, 20,
  /* 28 */  220, 20, 60,
  /* 29 */  000, 100, 000,
  /* 30 */  100, 149, 237,
  /* 31 */  255, 000, 000,
  /* 32 */  255, 180, 000,
  /* 33 */  135, 206, 235,
  /* 34 */  34, 140, 34,
  /* 35 */  255, 000, 255,
  /* 36 */  150, 150, 150,
  /* 37 */  255, 255, 255,
  /* 38 */  220, 000, 220,
  /* 39 */  000, 255, 000,
  /* 40 */  10, 200, 10,
  /* 41 */  220, 220, 255,
  /* 42 */  172, 255, 47,
  /* 43 */  124, 252, 000,
  /* 44 */  000, 250, 154,
  /* 45 */  000, 000, 000
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
  while (i < 44 && comando != Cores[i])
    i++;

  R = cores[i][0];
  G = cores[i][1];
  B = cores[i][2];
  delay(150);
  printaLed(R, G, B);
}

