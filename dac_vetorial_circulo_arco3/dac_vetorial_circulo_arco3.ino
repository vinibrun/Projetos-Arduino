/*
  Desenho vetorial em osciloscopio
  dac0 -> x
  dac1 -> y
  resolucao recomendada < 1024x1024 (deslocamento)

  Smile:
  circulo (1030, 1150, 70);
  circulo (1270, 1150, 70);
  arco (1150, 1000, 300, 350, 190, 1);

  Coracao:
  arco(1000, 1000, 100, 0, 220, 0);
  arco(1200, 1000, 100, 320, 180, 0);
  vetor(925, 930, 0);
  vetor(1100, 750, 1);
  vetor(1280, 930, 1);

  Rola:


  

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

void vetor(int x, int y, bool pinta) {
  if (pinta) {
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

void arco (int X0, int Y0, int raio, int ang0, int ang1, bool inverte) {
  int i;
  for (i = ang0 ; i != ang1; i += 1 - 2 * inverte) {
    if (i >= 360) i = 1;
    if (i <= 0) i = 359;
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
  arco(1000, 1000, 100, 320, 220, 0);
  vetor(1000, 1100, 0);
  vetor(1000, 1000, 1);
  vetor(920, 920, 0);
  vetor(920, 600, 1);
  vetor(1080, 920, 0);
  vetor(1080, 600, 1);
  arco(900, 550, 100, 60, 0, 0);
}
