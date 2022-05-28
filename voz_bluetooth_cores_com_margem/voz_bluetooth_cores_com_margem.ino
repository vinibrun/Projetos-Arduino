
#define Rout  9
#define Gout  10
#define Bout  11
#define Sin 7 // switch in

int R = 0, G = 0, B = 0, atual = 0, i, margem;
boolean cont = 0, mudanca;
String comando;

//**************************** MATRIZ DE CORES (NOMES)*******************
String Cores[35] = {
  /* 01 */  "*azul#",
  /* 02 */  "*a#",
  /* 03 */  "*b#",
  /* 04 */  "*amarelo#",
  /* 05 */  "*c#",
  /* 06 */  "*d#",
  /* 07 */  "*branco#",
  /* 08 */  "*cinza#",
  /* 09 */  "*laranja#",
  /* 10 */  "*abacaxi com banana é muito muito bom mesmo#",
  /* 11 */  "*0#",
  /* 12 */  "*roxo#",
  /* 13 */  "*verde#",
  /* 14 */  "*1#",
  /* 15 */  "*2#",
  /* 16 */  "*vermelho#",
  /* 17 */  "*#",
  /* 18 */  "*#",
  /* 19 */  "*violetta#",
  /* 20 */  "*ciano#",
  /* 21 */  "*rosa#",
  /* 22 */  "*o luquinhas acha que isso não vai funcionar#",
  /* 23 */  "*#",
  /* 24 */  "*prata#",
  /* 25 */  "*dourado#",
  //EASTER EGGS
  /* 26 */  "*meu nome é júlia#",
  /* 27 */  "*penta#",
  /* 28 */  "*tnt#",
  /* 29 */  "*abaixem a voz#",
  /* 30 */  "*força eletro#",
  /* 31 */  "*arduino maior que pic#",
  /* 32 */  "*vai safadão#",
  /* 33 */  "*isso não é um ovo de páscoa#",
  /* 34 */  "*a meta é rei#",
  /* 35 */  "*desligar#"
};
//**************************** MATRIZ DE CORES (RGB)*******************
int cores[35][3]  = {
  /* 01 */  000, 000, 200,
  /* 02 */  000, 000, 255,
  /* 03 */  000, 000, 139,
  /* 04 */  255, 255, 000,
  /* 05 */  255, 255, 200,
  /* 06 */  218, 165, 32,
  /* 07 */  255, 255, 255,
  /* 08 */  128, 128, 128,
  /* 09 */  255, 50, 000,
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
  /* 26 */  128, 43, 226,
  /* 27 */  20, 205, 20,
  /* 28 */  220, 20, 60,
  /* 29 */  000, 100, 000,
  /* 30 */  100, 149, 237,
  /* 31 */  255, 180, 000,
  /* 32 */  255, 255, 255,
  /* 33 */  220, 000, 220,
  /* 34 */  255, 020, 000,
  /* 35 */  000, 000, 000
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
  printaLed(0, 255, 0);
}

void loop() {
  do {
    comando = Serial.readString();
  } while (comando == "");
  comando.toLowerCase();
  Serial.println(comando);
  i = 0;
  while (i < 34/* && comando != Cores[i]*/) {
    i++;
  margem = comando.compareTo(Cores[i]);
  Serial.print("comando = ");
  Serial.print(comando);
  Serial.print("  Cores[i] = ");
  Serial.print(Cores[i]);
  Serial.print("  margem = ");
  Serial.println(margem);
  }
  R = cores[i][0];
  G = cores[i][1];
  B = cores[i][2];
  delay(150);
  printaLed(R, G, B);
}

