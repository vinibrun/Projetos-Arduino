
//transdutor - converte uma grandeza em sinal elétrico(ex.: sensor)
//entrega sinal para o micro fazer o tratamento
//entradas e saidas

/*
  Shield -> ARM: valor de tensão que define a potência na carga
  Shield -> ARM: detecta zero
  ARM -> Shield: pulso para iniciar a onda


  sai potencia na carga

  60Hz => T/2 = 8336uS
  detencta zero e conta até 833uS

*/
int valorPot, i = 0, y = 0;
bool zero;
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(A2, INPUT);
  digitalWrite(2, 0);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  valorPot = analogRead(A2);
  if (valorPot > 900)valorPot = 900;
  i = map(valorPot, 0, 1023, 0, 8333);
  //while (i < 200) {
  zero = digitalRead(3);
  if (valorPot == 900)digitalWrite(2, LOW);
  else if (zero) {
    //delayMicroseconds(i);
    digitalWrite(2, LOW);
    delayMicroseconds(i);
    digitalWrite(2, HIGH);
  }
  //i++;
  //}
  /*Serial.print(valorPot);
    Serial.print("   ");
    Serial.println(i);
  */
}
