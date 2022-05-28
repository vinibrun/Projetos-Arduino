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
int speede = 0, speedd = 0, sspeede, sspeedd;
int zeroh = 492;
int zerov = 512;
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

  Serial.print("vf=");
  Serial.print(vf);
  Serial.print("    vt=");
  Serial.print(vt);
  Serial.print("    vd=");
  Serial.print(vd);
  Serial.print("    ve=");
  Serial.print(ve);

  speede = vf - vt;
  speedd = vf - vt;

    if (ve && !vf) speede += ve;
    if (vd && !vf) speedd += vd;
    if (ve && !vt) speede -= ve;
    if (vd && !vt) speedd -= vd;
  /*else {
    speede = ve;
    speedd = vd;
    }*/

  Serial.print("    speede=");
  Serial.print(speede);
  Serial.print("    speedd=");
  Serial.print(speedd);



  sspeede = map(speede, -515, 515, 0, 180);        // reads the value of the potentiometer (value between 0 and 1023)
  sspeedd = map(speedd, -515, 515, 0, 180);

  if (sspeede > 95 || sspeede < 85)servoe.write(sspeede);
  else servoe.write(90);
  if (sspeedd > 95 || sspeedd < 85)servod.write(sspeedd);
  else servod.write(90);
  Serial.print("    sspeede=");
  Serial.print(sspeede);
  Serial.print("    sspeedd=");
  Serial.println(sspeedd);

}

