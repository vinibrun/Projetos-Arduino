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



*/

#define JoyxPin A0
#define JoyyPin A1
#define B1pin 2
#define B2pin 3
#define B3pin 4
#define B4pin 5
int xOld, yOld, xm, ym, xmOld, ymOld;
float pi = 3.14;
float seno [390], cosseno [390];
int vetores[10][2], circulos[10][3], arcos[10][6];
bool B1, B2, B3, B4;
  
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
  xOld =  X0 + (int) (raio * cosseno[ang1]);
  yOld =  Y0 + (int) (raio * seno[ang1]);
}

void mouse() {
  int posx = 1000, poxy = 1000, zerox = 512, zeroy = 512, i;
  
  valx = analogRead(JoyxPin) - zerox;
  valy = analogRead(JoyyPin) - zeroy;
  if (valx > 50 || valx < -50) posx += valx / 100;
  if (valy > 50 || valy < -50) posy += valy / 100;

  analogWrite(DAC1, posy);
  for(i=-5;i<5;i++) analogWrite(DAC0, posx + i);
  analogWrite(DAC0, posx);
  for(i=-5;i<5;i++) analogWrite(DAC1, posy + i);

  xm = posx;
  ym = posy;
}

void desenha_vetor(){


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
  B1 = digitalRead(B1pin);
  B2 = digitalRead(B2pin);
  B3 = digitalRead(B3pin);
  B4 = digitalRead(B4pin);
  if(B1){
    desenha_vetor();
    }
    
    }
  mouse();
  printa();
}
