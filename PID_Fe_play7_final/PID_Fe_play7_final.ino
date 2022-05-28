/*
  STEPKIDS

  Esse código faz uma leitura em um potenciômetro de dois eixos,
  processa o sinal e o transforma em comandos para dois motores DC.
  A etapa de potência é feita por dois Victor's 844, portanto o sinal
  enviado segue o padrão servo
*/

#include <Servo.h>

Servo servoe;  // cria servo da esquerda
Servo servod;  // cria servo da direita

int potpinv = A0; // pino do pot vertical
int potpinh = A1; // pino do pot horizontal
int valv;  // valor do pot vertical
int valh;    // valor do pot vertical
int speede = 0, speedd = 0, sspeede, sspeedd; //variáveis de velocidade
int zeroh = 503; //zero horizontal
int zerov = 520; //zero vertical
int vf, vt, vd, ve; // velocidades para frente, trás, direita e esquerda

void setup() {
  servod.attach(9); //configura os pinos dos servos
  servoe.attach(10);
  Serial.begin(9600);
}

void loop() {
  valv = analogRead(potpinv);
  valh = analogRead(potpinh);

  /* // feedback
    Serial.print("valv=");
    Serial.print(valv);
    Serial.print("    valh=");
    Serial.print(valh);
  */

  //transforma o sinal dos pots em comandos nos 4 sentidos
  if (valv > zerov + 10) {
    vf = valv - zerov;
    vt = 0;
  }
  else if (valv < zerov - 10) {
    vf = 0;
    vt = - valv + zerov;
  }
  else {
    vf = 0;
    vt = 0;
  }
  if (valh > zeroh + 10) {
    ve = valh - 500;
    vd = 0;
  }
  else if (valh < zeroh - 10) {
    ve = 0;
    vd = - valh + 512;
  }
  else
  {
    vd = 0;
    ve = 0;
  }
  if (vf > 512) vf = 512;
  if (vt > 512) vt = 512;
  if (ve > 512) ve = 512;
  if (vd > 512) vd = 512;

  /* //feedback
    Serial.print("    vf=");
    Serial.print(vf);
    Serial.print("    vt=");
    Serial.print(vt);
    Serial.print("    vd=");
    Serial.print(vd);
    Serial.print("    ve=");
    Serial.print(ve);
  */
  // transforma comandos nos 4 sentidos para velocidades dos servos
  speede = vf - vt;
  speedd = vf - vt;

  if (ve && !vf) speede += ve / 4;
  if (vd && !vf) speedd += vd / 4;
  if (ve && !vt) speede -= ve / 4;
  if (vd && !vt) speedd -= vd / 4;
  if (vt < 30 && vf < 30) {
    speede = vd;
    speedd = ve;
  }

  /* //feedback
    Serial.print("    speede=");
    Serial.print(speede);
    Serial.print("    speedd=");
    Serial.print(speedd);
  */


  sspeede = map(speede, -515, 515, 70, 110); // 70 e 110 são as velocidades relativas dos motores
  sspeedd = map(speedd, -515, 515, 70, 110); // quanto mais próximas de 90, menor a velocidade

  // envia as velocidades de servo para os servos
  if (sspeede > 95 || sspeede < 85)servoe.write(sspeede);
  else servoe.write(90);
  if (sspeedd > 95 || sspeedd < 85)servod.write(sspeedd);
  else servod.write(90);

  /*//feedback
    Serial.print("    sspeede=");
    Serial.print(sspeede);
    Serial.print("    sspeedd=");
    Serial.println(sspeedd);
  */
}

