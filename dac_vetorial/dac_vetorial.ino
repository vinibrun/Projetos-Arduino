/*
  Desenho vetorial em osciloscopio
  dac0 -> x
  dac1 -> y
  resolucao -> 128 x 128

*/

int xOld, yOld;

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

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  analogWriteResolution(12);
  xOld = 0;
  yOld = 0;
}

void loop() {
  vetor(1095, 0);
  vetor(512,1024);
  vetor(127, 512);
}
