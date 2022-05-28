/*
  Desenho vetorial em osciloscopio
  dac0 -> x
  dac1 -> y
  resolucao -> 128 x 128

*/

int xOld, yOld;
float pi = 3.14;
float seno [390], cosseno [390];


void liga_seno_cosseno() {
  float i;
  int j = 0;
  for (i = 0.01; i < 2 * pi - 0.001; i += pi / 180) {
    seno[j] = sin(i);
    j++;
  }
  j = 0;
  for (i = 0.01; i < 2 * pi - 0.001; i += pi / 180) {
    cosseno[j] = cos(i);
    j++;
  }
}

void vetor(int x, int y) {
  float Dx = (float)x - (float)xOld;
  float Dy = (float)y - (float)yOld;
  float Vlen = Dx * Dx + Dy * Dy;
  int Pnum = (int)Vlen / 1000;
  float xPasso = Dx / (float)Pnum;
  float yPasso = Dy / (float)Pnum;
  float j;
  for (j = 0; j < Pnum; j++) {
    analogWrite(DAC0, xOld + (int)(j * xPasso));
    analogWrite(DAC1, yOld + (int)(j * yPasso));
  }
  xOld = x;
  yOld = y;
}

void circulo (int X0, int Y0, int raio) {
  int i;
  for (i = 0; i < 360; i++) {
    analogWrite(DAC0, X0 + (int) (raio * cosseno[i]));
    analogWrite(DAC1, Y0 + (int) (raio * seno[i]));
  }
}

void arco (int X1, int Y1, int X2, int Y2, bool inverte) {
  int i, raio, X0, Y0;
  float Dx = (float)X1 - (float)X2;
  float Dy = (float)Y1 - (float)Y2;
  float Vlen = Dx * Dx + Dy * Dy;
  raio = (int) sqrt(Vlen);
  X0 = (X1 + X2) / 2;
  Y0 = (X1 + X2) / 2;
  for (i = 0 + 180 * inverte; i < 180 + 180 * inverte; i++) {
    analogWrite(DAC0, X0 + (int) (raio * cosseno[i]));
    analogWrite(DAC1, Y0 + (int) (raio * seno[i]));
  }
}


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  analogWriteResolution(12);
  xOld = 0;
  yOld = 0;
  liga_seno_cosseno();
}


void loop() {
  circulo (1100, 1300, 400);
  //circulo (1300, 1300, 100);
  arco (1100, 1200, 1300, 1200, 1);
  /*
    vetor(1095, 0);
    vetor(512, 1024);
    vetor(127, 512);
  */
}
