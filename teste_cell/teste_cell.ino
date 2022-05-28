#include <HX711.h>



const int DOUT = A1;      // Pino DT placa HX711
const int hxSCK = A2;     // Pino SCK placa HX711

void setup() {
  Serial.begin(9600);
  pinMode(hxSCK, OUTPUT);
  pinMode(DOUT, INPUT);
  // reseta o conversor HX711
  digitalWrite(hxSCK, 1);  
  delay (200);
  digitalWrite(hxSCK, LOW); 
  // -------------------------
   Serial.println(" INICIO");
}

void loop() {
  
     Serial.print(Converte());
     Serial.println(" AMOSTRA");
     delay (1000); //Aguarda 1 segundo

}


unsigned long Converte(){
 unsigned long CAPTURA = 0;  
  digitalWrite(hxSCK, LOW); 
  while (digitalRead(DOUT)==1) ;
  for (int i=0; i<24; i++){             // loop 24 pulsos
        digitalWrite(hxSCK, HIGH); 
        CAPTURA = CAPTURA<<1;
        //delayMicroseconds(10); 
        digitalWrite(hxSCK, LOW);
        if(digitalRead(DOUT) == 1) CAPTURA++;
        } 
   // pulso extra 25 pulsos próxima leitura do HX711 canal A ganho 128***     
   digitalWrite(hxSCK, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(hxSCK, LOW);
   //-------------------------------------------------------
 CAPTURA ^= 0x00800000; 
  
 return CAPTURA;
}
