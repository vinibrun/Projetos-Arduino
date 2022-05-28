#define BotaoPin 2
#define MotorAPin 10
#define MotorFPin 11
#define ChaveAPin 5
#define ChaveFPin 6

int AbreVelocidade = 235;  // 0 a 255
int FechaVelocidade = 235; // 0 a 255


bool UltimoComando = 0; // 0 = fechou, 1 = abriu;
bool Botao;             // 0 = solto, 1 = pressionado
int Estado,var=0;            // 0 = fechado, 1 = andando,  2 = aberto
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
  Serial.print("  var ");
  Serial.print(var);
  Serial.print("  UltimoComando ");
  Serial.println(UltimoComando);

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
    var = 2;             // Se chave aberto, aberto
    UltimoComando = 1;
  }
  if (!ChaveF) {
    var = 0;  // Se chave fechado, fechado
    UltimoComando = 0;
  }
  
  if (!Botao){
    delay(100);
    while(!Botao)AtualizaChaves();
    delay(100);
    var++;
    if(var > 3) var = 0;
  }
  if(var == 0){
    analogWrite(MotorAPin, 0);
    analogWrite(MotorFPin, 0);
  }
  if(var == 1){
    analogWrite(MotorAPin, 0);
    analogWrite(MotorFPin, FechaVelocidade);
  }
  if(var == 2){
    analogWrite(MotorAPin, 0);
    analogWrite(MotorFPin, 0);
  }
  if(var == 3){
    analogWrite(MotorAPin, AbreVelocidade);
    analogWrite(MotorFPin, 0);
  }
  delay(100);
}








