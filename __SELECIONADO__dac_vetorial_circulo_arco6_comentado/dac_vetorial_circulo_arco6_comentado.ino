/*
  Desenho vetorial em osciloscopio
  
  Componentes:
  Arduino Due;
  Osciloscopio com 2 canais e funcao X-Y.

  Montagem: 
  interligar terra do osciloscopio e do arduino;
  ponteira 1 na porta DAC0 (acoplamento CA);
  ponteira 2 na porta DAC1 (acoplamento CA);
  osciloscopio na funcao X-Y.
  escala: 50mV / div (alterar e observar efeito)

  dac0 -> x
  dac1 -> y
  resolucao recomendada < 1024x1024 (deslocamento)

  Exemplos -> copiar no loop 
    
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
  arco(1000, 1000, 150, 250, 290, 1); // rosto
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


  macetes:
   - cada osciloscopio tem suas particularidades e distorce as imagns de um jeito. Desafio quem usar esse codigo a corrigir as imperfeicoes e compartilhar;
   - desenhos muito grandes distorcem a imagem devido ao processamento limitado do Due;
   - percebi que os nossos osciloscopios fazem um borrao no eixo y, por isso a resoloucao em y eh menor do que em x, agilizando o processo
   - facam mais desenhos e compartilhem na pagina do Arduino ;)

Autor: Vinicius Brun Kriesang, tecnico em eletronica pela Fundacao Liberato - Novo Hmaburgo, RS
https://www.facebook.com/vinicius.brunkriesang
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
  /*  o vetor parte do ultimo ponto pintado.
   *  parametros: 
   *  x e y finais (o vetor parte do último pixel pintado);
   *  habilitador (pinta ou não).
   */
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

void circulo (int X0, int Y0, int raio) { /*
  parametros:
  x e y do centro do circulo;
  raio.
  */
  int i;
  for (i = 0; i < 360; i++) {
    analogWrite(DAC0, X0 + (int) (raio * cosseno[i]));
    analogWrite(DAC1, Y0 + (int) (raio * seno[i]));
  }
}

void arco (int X0, int Y0, int raio, int ang0, int ang1, bool inverte) { /*
  cria um arco, definindo raio, e os angulos limites
  parametros: 
  x e y do centro;
  angulo inicial;
  angulo final;
  horario ou anti-horario;
 */
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
  analogWriteResolution(12);
  xOld = 0;
  yOld = 0;
  liga_seno_cosseno();
}


void loop() {
  // cole aqui os exemplos para comecar a brincadeira :D
  
  arco(1000, 1000, 150, 250, 290, 1); // rosto
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
}
