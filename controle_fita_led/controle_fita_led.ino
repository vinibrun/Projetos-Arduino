
#define Rout  9
#define Gout  10
#define Bout  11
#define Sin 7 // switch in

int R = 0, G = 0, B = 0, atual = 0;
boolean cont = 0, mudanca;

//**********MATRIZ DE CORES*************
// inteiros
int cores[28][3]  = { // todas combinações possíveis considerando 0, 127 e 255
  0, 0, 0,
  0, 0, 255,
  0, 255, 0,
  0, 255, 255,
  255, 0, 0,
  255, 0, 255,
  255, 255, 0,
  255, 255, 255,

  //quebrados
  128, 0, 0,
  128, 0, 128,
  128, 0, 255,
  128, 128, 0,
  128, 128, 128,
  128, 128, 255,
  128, 255, 0,
  128, 255, 128,
  128, 255, 255,

  0, 128, 0,
  0, 128, 128,
  0, 128, 255,
  255, 128, 0,
  255, 128, 128,
  255, 128, 255,

  0, 0, 128,
  0, 255, 128,
  255, 0, 128,
  255, 255, 128
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
  mudanca = digitalRead(Sin);
  if (mudanca) {
    delay(150);
    do {
      mudanca = digitalRead(Sin);
      printaLed(R, G, B);
    } 
    while (mudanca);
    //if (atual++ > 27) atual = 0;  // trocar em ordem
    atual = random(1,28);
    R = cores[atual][0];
    G = cores[atual][1];
    B = cores[atual][2];
    delay(150);
  }

  printaLed(R, G, B);


  /*
    Serial.print("R: ");
   Serial.print(R);
   Serial.print(" G: ");
   Serial.print(G);
   Serial.print(" B: ");
   Serial.println(B);
   */
}

