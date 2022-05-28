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
  arco(1000, 1000, 100, 320, 220, 0);
  vetor(1000, 1100, 0);
  vetor(1000, 1000, 1);
  vetor(920, 920, 0);
  vetor(920, 660, 1);
  vetor(1080, 920, 0);
  vetor(1080, 660, 1);
  arco(900, 550, 100, 0, 75, 1);
  arco(1100, 550, 100, 180, 105, 0);

  Arvore:
  arco(1000, 1000, 100, 90, 280, 1);
  vetor(1015, 800, 1);
  arco(1000, 1000, 100, 90, 260, 0);
  vetor(985, 800, 1);
  arco(935, 800, 50, 0, 270, 1);
  arco(1065, 800, 50, 180, 270, 0);

  L + Arvore:
  vetor(1150, 1100, 0);
  vetor(1150, 800, 1);
  vetor(1350, 800, 1);
  vetor(1350, 900, 1);
  vetor(1250, 900, 1);
  vetor(1250, 1100, 1);
  vetor(1150, 1100, 1);

  arco(1000, 1000, 100, 90, 280, 1);
  vetor(1025, 800, 1);
  arco(1000, 1000, 100, 90, 260, 0);
  vetor(985, 800, 1);
  arco(935, 800, 50, 0, 270, 1);
  arco(1065, 800, 50, 180, 270, 0);

  Coelho:  
  arco(1000, 1000, 150, 250, 290, 1); // rosro
  circulo(930,1050,30); // olho esquerdo
  circulo(1070,1050,30); // olho direito
  arco(1200, 1230, 300, 200, 150, 1); // orelha esquerda esquerda
  arco(675, 1230, 300, 345, 30, 0); // orelha esquerda direita
  arco(1325, 1230, 300, 195, 150, 1); // orelha direita esquerda
  arco(800, 1230, 300, 340, 30, 0); // orelha direita direita
  vetor(950, 900, 0); // ----- dentes
  vetor(950, 800, 1);
  vetor(1050, 800, 1);
  vetor(1050, 900, 1);
  vetor(950, 900, 1);
  vetor(1000, 900, 0);
  vetor(1000, 800, 1); // ------
  vetor(970, 1000, 0);// --- nariz
  vetor(1030, 1000, 1);
  vetor(1000, 950, 1);
  vetor(970, 1000, 1);// -----
  vetor(1110, 950, 0); // bigodes direita
  vetor(1180, 950, 1);
  vetor(1100, 980, 0);
  vetor(1170, 1050, 1);
  vetor(1100, 920, 0);
  vetor(1170, 850, 1);  // ----
  vetor(890, 950, 0); // bigodes esquerda
  vetor(810, 950, 1);
  vetor(900, 980, 0);
  vetor(800, 1050, 1);
  vetor(900, 920, 0);
  vetor(800, 850, 1);  // ----

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
    int Pnum = (int)Vlen / 100;
    float xPasso = Dx / (float)Pnum;
    float yPasso = Dy / (float)Pnum;
    int j;
    for (j = 0; j < Pnum; j++) {
      analogWrite(DAC0, xOld + (int)(j * xPasso));
      if(!(j%10)) analogWrite(DAC1, yOld + (int)(j * yPasso));
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
  for (i = ang0 ; i != ang1; i += (1 - 2 * inverte)) {
    if (i >= 360) i = 1;
    if (i <= 0) i = 359;
    analogWrite(DAC0, X0 + (int) (raio * cosseno[i]));
    analogWrite(DAC1, Y0 + (int) (raio * seno[i]));
  }
  xOld =  X0 + (int) (raio * cosseno[ang1]);
  yOld =  Y0 + (int) (raio * seno[ang1]);
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
  vetor(1150, 1100, 0);
  vetor(1150, 800, 1);
  vetor(1350, 800, 1);
  vetor(1350, 900, 1);
  vetor(1250, 900, 1);
  vetor(1250, 1100, 1);
  vetor(1150, 1100, 1);

  arco(1000, 1000, 100, 90, 280, 1);
  vetor(1025, 800, 1);
  arco(1000, 1000, 100, 90, 260, 0);
  vetor(985, 800, 1);
  arco(935, 800, 50, 0, 270, 1);
  arco(1065, 800, 50, 180, 270, 0);

}
