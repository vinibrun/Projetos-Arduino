
#include <LiquidCrystal.h>
#include <HX711.h>

#define DOUT  A2
#define CLK  A1

HX711 balanza(DOUT, CLK);
long zero;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
bool lendo = 0, liga = 0, Tok = 0, direita = 0, esquerda = 0, baixo = 0, cima = 0, select = 0;
long Tinicio = 0, Tinst = 0, Tmax = 0, SvalN = 0, Smax = 0;
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
    lcd.print("T.inst:");
    lcd.print(Tinst);
    lcd.print("ms");
    lcd.setCursor(0, 1);
    lcd.print("F.inst:");
    lcd.print(SvalN);
    lcd.print("N");
  }
  if (tela == 3) {
    lcd.setCursor(0, 0);
    lcd.print("T. max:");
    lcd.print(Tmax);
    lcd.print("ms");
    lcd.setCursor(0, 1);
    lcd.print("F. max:");
    lcd.print(Smax);
    lcd.print("N");
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.begin(9600);
  Serial.print("Lectura del valor del ADC:\t");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  zero = 0;
  for (i = 0; i < 10; i++) {
    zero += balanza.read();
  }
  Serial.println(zero);
  zero = zero / 10;
  balanza.set_scale(439430.25); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.

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
    for (i = 0; i < 10; i++) {
      zero += balanza.read();
    }
    Serial.println(zero);
    zero = zero / 10;
  }

  if (liga && !lendo) {
    Smax = 0;
    Tmax = 0;
    Tinst = 0;
    Tinicio = millis();
    lendo = 1;
    liga = 0;
  }
  else if (liga && lendo) {
    liga = 0;
    lendo = 0;
  }

  if (lendo) {
    Tinst = millis() - Tinicio;
    long peso = balanza.read();
    SvalN = peso - zero;
    if (SvalN > Smax) {
      Smax = SvalN;
      Tmax = Tinst;
    }
  }




  if (j > 5) {
    printa(menu);
    j = 0;
  }
  else j++;
  delay(100);

}















