#include <HX711.h>

#define DOUT  A2
#define CLK  A1

HX711 balanza(DOUT, CLK);
long zero;
void setup() {
Serial.begin(9600);
  Serial.print("Lectura del valor del ADC:\t");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  int i;
  zero = 0;
  for (i=0;i<10;i++){
    zero += balanza.read();
    }
    Serial.println(zero);
  zero = zero / 10;
  balanza.set_scale(439430.25); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  
}

void loop() {
  long peso = balanza.read();
  
  Serial.print("Peso:\t");
  Serial.print(peso-zero);
  Serial.println("unidade aleatoria");
  delay(500);
}

