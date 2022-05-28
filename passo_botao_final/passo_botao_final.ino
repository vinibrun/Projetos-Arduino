/* Roteiro para ligar o circuito
 *  conectar a fonte de alimentação nos pinos da Ponte H - Povitivo no +12V, negativo - GND
 *  
 *  
 */




#define Botao1Pin 2 // pino do botao 1
#define Botao2Pin 3 // pino do botao 2


// configuracoes
int voltas_abrir = 100;
int voltas_fechar = 100;
int tempo = 300; // tempo entre os passos. minimo: 200


// Conexoes no Arduino

int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;





bool UltimoComando = 0; // 0 = fechar, 1 = abrir


bool passos[4][4] = {
  1, 0, 1, 0,
  0, 0, 1, 1,
  0, 1, 0, 1,
  1, 1, 0, 0
};


void abre(int voltas) {
  int i, j, k;
  for (k = 0; k < (50 * voltas); k++) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        digitalWrite((j + IN1), passos[i][j]);
        delayMicroseconds(tempo);
      }
    }
  }
  for (j = 0; j < 4; j++) digitalWrite((j + IN1), 0);
  UltimoComando = 1;
}

void fecha(int voltas) {
  int i, j, k;
  for (k = 0; k < (50 * voltas); k++) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        digitalWrite((j + IN1), passos[3 - i][j]);
        delayMicroseconds(tempo);
      }
    }
  }
  for (j = 0; j < 4; j++) digitalWrite((j + IN1), 0);
  UltimoComando = 0;
}


void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(Botao1Pin, INPUT_PULLUP);
  pinMode(Botao2Pin, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop()
{
  if (!digitalRead(Botao1Pin)) {
    Serial.println("botao1");
    if (UltimoComando) fecha(voltas_fechar);
    else abre(voltas_abrir);
    while (!digitalRead(Botao1Pin));
  }
  if (!digitalRead(Botao2Pin)) {
    Serial.println("botao2");
    if (UltimoComando) {
      do {
        fecha(1);
        UltimoComando = 0;
      } while (!digitalRead(Botao2Pin));
    }
    else
      do {
        abre(1);
        UltimoComando = 1;
      } while (!digitalRead(Botao2Pin));
  delay(1000);
  }
  delay(10);
}






