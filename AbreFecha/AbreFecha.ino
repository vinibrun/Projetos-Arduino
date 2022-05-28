#define BotaoPin 2
#define MotorAPin 9
#define MotorFPin 10
#define ChaveAPin 5
#define ChaveFPin 6

int TempoAbrir  = 3000; // ms
int TempoFechar = 3000; // ms


bool UltimoComando = 0; // 0 = fechou, 1 = abriu;
bool Botao;      // 0 = solto, 1 = pressionado
char Estado; // 0 = fechado, 1 = andando,  2 = aberto
bool ChaveA;     // 0 = solto, 1 = pressionado
bool ChaveF;     // 0 = solto, 1 = pressionado

void AtualizaChaves(){
  Botao  = digitalRead (BotaoPin);
  ChaveA = digitalRead (ChaveAPin);
  ChaveF = digitalRead (ChaveFPin);
}

void Abre(){
  digitalWrite(MotorAPin, HIGH);
  digitalWrite(MotorFPin, LOW);
  int i;
  for(i=0;i<10;i++){
    delay(TempoAbrir/10);
    AtualizaChaves();
    if(ChaveF) i = 10;
  }
  UltimoComando = 1;
}

void Fecha(){
  digitalWrite(MotorAPin, LOW);
  digitalWrite(MotorFPin, HIGH);
  int i;
  for(i=0;i<10;i++){
    delay(TempoFechar/10);
    AtualizaChaves();
    if(ChaveA) i = 10;
  }
  UltimoComando = 0;
}





void setup {
  pinMode(BotaoPin, INPUT);
  pinMode(ChaveAPin, INPUT);
  pinMode(ChaveFPin, INPUT);
  pinMode(MotorAPin, OUTPUT);
  pinMode(MotorFPin, OUTPUT);
}


void loop {
  AtualizaChaves();
  if (ChaveA) Estado = 2;             // Se chave aberto, aberto
  if (ChaveF) Estado = 0;             // Se chave fechado, fechado
  if (!ChaveA && !ChaveF) Estado = 1; // Se not fechado e not aberto, andando

  if (Botao){
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
}




