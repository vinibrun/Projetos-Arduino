
#include <LiquidCrystal.h>
#include <HX711.h>

#define DOUT  A2
#define CLK  A1

HX711 balanza(DOUT, CLK);
long zero;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
bool lendo = 0, liga = 0, Tok = 0, direita = 0, esquerda = 0, baixo = 0, cima = 0, select = 0;
long Tinicio = 0, Tinst = 0, Tmax = 0, SvalN = 0, Smax = 0, Tmin = 0, Smin = 0, CoefX = 95, CoefY = 5, CoefZ = -4451;
long U0 = 0, U1 = 0, U2 = 0, U3 = 0, U4 = 0, med = 0, F0 = 1000, peso = 0;
int menu = 0, i = 0, j = 0;
/*  Telas do Menu
  1234567890123456
  0:
  Bianca e Aila
  Lindonas

  1:
  Iniciar leitura OU Parar leitura


  2:
  T.inst:XXXXXXXms
  F.inst:XXXXXXXXN

  3:
  T. Max:XXXXXXXms
  F. Max:XXXXXXXXN

*/

void printa(int tela) {
  lcd.clear();
  if (tela == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Bianca e Aila");
    lcd.setCursor(0, 1);
    lcd.print("Lindonas!");
  }
  if (tela == 1) {
    lcd.setCursor(0, 0);
    if (!lendo) lcd.print("Iniciar Leitura");
    else  lcd.print("Parar Leitura");
  }
  if (tela == 2) {
    lcd.setCursor(0, 0);
    lcd.print("F. max:");
    lcd.print(Smax);
    lcd.print("N");
    lcd.setCursor(0, 1);
    lcd.print("F.inst:");
    lcd.print(SvalN);
    lcd.print("N");
  }
  if (tela == 3) {
    lcd.setCursor(0, 0);
    lcd.print("F. min:");
    lcd.print(Smin);
    lcd.print("N");
    lcd.setCursor(0, 1);
    lcd.print("F.inst:");
    lcd.print(SvalN);
    lcd.print("N");
  }
  if (tela == 4) {
    lcd.setCursor(0, 0);
    lcd.print("F. est:");
    lcd.print(Smin);
    lcd.print("N");
    lcd.setCursor(0, 1);
    lcd.print("F.inst:");
    lcd.print(SvalN);
    lcd.print("N");
  }
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println(balanza.read());
  zero = 0;
  for (i = 0; i < 3; i++) {
    zero += balanza.read();
  }
  Serial.println(zero);
  zero = zero / 3;
  balanza.set_scale(439430.25); 
  balanza.tare(20);  

  Serial.println("Listo para pesar");

}
void loop() {
  int botao;
  botao = analogRead (A0);
  if (botao < 100) {
    while (botao < 100) {
      botao = analogRead (A0);
      delay(10);
    }
    direita = 1;
  }
  else if (botao < 200) {
    while (botao < 200) {
      botao = analogRead (A0);
      delay(10);
    }
    cima = 1;
  }
  else if (botao < 400) {
    while (botao < 400) {
      botao = analogRead (A0);
      delay(10);
    }
    baixo = 1;
  }
  else if (botao < 600) {

    while (botao < 600) {
      botao = analogRead (A0);
      delay(10);
    }
    esquerda = 1;
  }
  else if (botao < 800) {
    while (botao < 800) {
      botao = analogRead (A0);
      delay(10);
    }
    select = 1;
  }

  if (cima) {
    cima = 0;
    menu++;
    if (menu > 3) menu = 0;
  }
  if (baixo) {
    baixo = 0;
    menu--;
    if (menu < 0) menu = 3;
  }
  if (select) {
    select = 0;
    liga = 1;
  }
  if (direita) {
    direita = 0;
    zero = 0;
    for (i = 0; i < 3; i++) {
      zero += balanza.read();
    }
    Serial.println(zero);
    zero = zero / 3;
  }

  if (liga && !lendo) {
    Smax = 0;
    Smin = 0;
    lendo = 1;
    liga = 0;
  }
  else if (liga && lendo) {
    liga = 0;
    lendo = 0;
  }

  if (lendo) {
    peso = balanza.read();
    SvalN = (((peso - zero) * CoefY) / CoefX) + CoefZ;
    SvalN = SvalN / 10;
    SvalN = SvalN * 10;
    if (SvalN > Smax) {
      Smax = SvalN;
    }
    if (SvalN < Smin) {
      Smin = SvalN;
    }
  }




  if (j > 5) {
    printa(menu);
    j = 0;
    Serial.println(SvalN);
  }
  else j++;
  delay(100);

}















