/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo servoe;  // create servo object to control a servo
Servo servod;  // create servo object to control a servo

int potpinv = A0;
int potpinh = A1;  // analog pin used to connect the potentiometer
int valv;  // analog pin used to connect the potentiometer
int valh;    // variable to read the value from the analog pin
int sspeede = 0, sspeedd = 0;
int zeroh = 484;
int zerov = 514;
int vf, vt, vd, ve;

void setup() {
  servod.attach(9);  // attaches the servo on pin 9 to the servo object
  servoe.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  valv = analogRead(potpinv);
  valh = analogRead(potpinh);
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
    ve = valh - 512;
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
  Serial.print("vf=");
  Serial.print(vf);
  Serial.print("    vt=");
  Serial.print(vt);
  Serial.print("    vd=");
  Serial.print(vd);
  Serial.print("    ve=");
  Serial.println(ve);
/*
  
  sspeede = //(-valh + zeroh) +  (valv - zerov);  // reads the value of the potentiometer (value between 0 and 1023)
    sspeedd = //(valh - zeroh) +          (valv - zerov);


      sspeede = map(sspeede, 0, 1023, 0, 180);        // reads the value of the potentiometer (value between 0 and 1023)
  sspeedd = map(sspeedd, 0, 1023, 0, 180);
  servoe.write(sspeede);                // sets the servo position according to the scaled value
  servod.write(sspeedd);                  // sets the servo position according to the scaled value
  Serial.print("valv");                  // sets the servo position according to the scaled value
  Serial.print("  ");                  // sets the servo position according to the scaled value
  Serial.print(valv);                 // sets the servo position according to the scaled value
  Serial.print("valh");                  // sets the servo position according to the scaled value
  Serial.print("  ");                  // sets the servo position according to the scaled value
  Serial.print(valh);                 // sets the servo position according to the scaled value
  Serial.print("sspeedd");                  // sets the servo position according to the scaled value
  Serial.print("  ");                  // sets the servo position according to the scaled value
  Serial.print(sspeedd);                 // sets the servo position according to the scaled value
  Serial.print("  ");                  // sets the servo position according to the scaled value
  Serial.print("sspeede");                  // sets the servo position according to the scaled value
  Serial.print("  ");                  // sets the servo position according to the scaled value
  Serial.println(sspeede);
  delay(15);                           // waits for the servo to get there
*/
}

