#define BotaoPin 2
#define MotorAPin 9
#define MotorFPin 10
#define ChaveAPin 5
#define ChaveFPin 6

int AbreVelocidade = 100;  // 0 a 255
int FechaVelocidade = 100; // 0 a 255


bool UltimoComando = 0; // 0 = fechou, 1 = abriu;
bool Botao;             // 0 = solto, 1 = pressionado
int Estado;            // 0 = fechado, 1 = andando,  2 = aberto
bool ChaveA;            // 0 = solto, 1 = pressionado
bool ChaveF;            // 0 = solto, 1 = pressionado

void AtualizaChaves(){
  Botao  = digitalRead (BotaoPin);
  ChaveA = digitalRead (ChaveAPin);
  ChaveF = digitalRead (ChaveFPin);
  Serial.print("Botao ");
  Serial.print(Botao);
  Serial.print("  ChaveA ");
  Serial.print(ChaveA);
  Serial.print("  ChaveF ");
  Serial.print(ChaveF);
  Serial.print("  Estado ");
  Serial.print(Estado);
  Serial.print("  UltimoComando ");
  Serial.println(UltimoComando);

}

void Abre(){
  analogWrite(MotorAPin, AbreVelocidade);
  analogWrite(MotorFPin, 0);
  do{
    AtualizaChaves();
    delay(100);  
  }
  while((!ChaveF ||Estado ==1) && !Botao);
  UltimoComando = 1;
}

void Fecha(){
  analogWrite(MotorAPin, 0);
  analogWrite(MotorFPin, FechaVelocidade);
  do{
    AtualizaChaves();
    delay(100);  
  }
  while((!ChaveA ||Estado ==1) && !Botao);
  UltimoComando = 0;
}





void setup () {
  pinMode(BotaoPin, INPUT_PULLUP);
  pinMode(ChaveAPin, INPUT_PULLUP);
  pinMode(ChaveFPin, INPUT_PULLUP);
  pinMode(MotorAPin, OUTPUT);
  pinMode(MotorFPin, OUTPUT);
  Serial.begin(9600);
  AtualizaChaves();
}


void loop () {
  AtualizaChaves();
  if (!ChaveA) {
    Estado = 2;             // Se chave aberto, aberto
    UltimoComando = 1;
  }
  if (!ChaveF) {
    Estado = 0;  // Se chave fechado, fechado
    UltimoComando = 0;
  }
  if (ChaveA && ChaveF) Estado = 1; // Se not fechado e not aberto, andando

  if (!Botao){
    delay(100);
    while(!Botao)AtualizaChaves();
    delay(100);
    Estado++;
    if(Estado > 2) Estado = 0;
  }
    if(Estado == 2) { // se aberto, fecha
      Fecha();
    }
    else if(Estado == 0) { //se fechado, abre
      Abre();    
    }
    else if(Estado == 1) { //se nem aberto, nem fechado
      if(UltimoComando) { // se abriu, fecha
        Fecha();  
      } 
      if(!UltimoComando) { // se fechou, abre
        Abre();  
      }
    }
  }
  delay(100);
}







