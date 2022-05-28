// Conexoes modulo - Arduino
int IN1 = 8; // 8
int IN2 = 9; // 11
int IN3 = 10; // 9
int IN4 = 11; // 10

int tempo = 300; // tempo minimo: 250




bool passos[4][4] = {
  1,0,1,0, 
  0,0,1,1,
  0,1,0,1,
  1,1,0,0
};

void frente(int voltas){
  int i,j,k;
  for (k=0;k<(50*voltas);k++){
    for (i=0;i<4;i++){
      for(j=0;j<4;j++){
        digitalWrite((j+IN1),passos[i][j]);
        delayMicroseconds(tempo);
      }
    }
  }
  for(j=0;j<4;j++) digitalWrite((j+IN1),0);
}

void tras(int voltas){
  int i,j,k;
  for (k=0;k<(50*voltas);k++){
    for (i=0;i<4;i++){
      for(j=0;j<4;j++){
        digitalWrite((j+IN1),passos[3-i][j]);
        delayMicroseconds(tempo);
      }
    }
  }
  for(j=0;j<4;j++) digitalWrite((j+IN1),0);
}

void setup()
{
  // Define os pinos como saida
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  String comando = Serial.readString();
    tras (comando.toInt());
    frente (comando.toInt());
    tras (comando.toInt());
    frente (comando.toInt());
  /*

   
   // Passo 1
   digitalWrite(IN1, 1);
   digitalWrite(IN2, 0);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 1);
   delay(tempo);  
   
   // Passo 2
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 1);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 1);
   delay(tempo);
   
   // Passo 3
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 1);
   digitalWrite(IN3, 1);
   digitalWrite(IN4, 0);
   delay(tempo);
   
   // Passo 4
   digitalWrite(IN1, 1);
   digitalWrite(IN2, 0);
   digitalWrite(IN3, 1);
   digitalWrite(IN4, 0);
   delay(tempo);
   */
}





