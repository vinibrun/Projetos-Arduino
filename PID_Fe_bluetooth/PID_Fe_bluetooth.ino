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

int velocidades[10][2]{
  90,90,
  90,180,
  0,0,
  180,90,
  180,130,
  0,50,
  50,0,
  130,180
  };


int potpinv = A0;
int potpinh = A1;  // analog pin used to connect the potentiometer
int valv;  // analog pin used to connect the potentiometer
int valh;    // variable to read the value from the analog pin
int speede = 0, speedd = 0, sspeede, sspeedd;
int zeroh = 503;
int zerov = 520;
int vf, vt, vd, ve;
int BTnum;
int multiplicador;


void setup() {
  servod.attach(9);  // attaches the servo on pin 9 to the servo object
  servoe.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  String comando = Serial.readString();
  BTnum = comando.toInt();
    sspeede = velocidades[BTnum][0];
    sspeedd = velocidades[BTnum][0];
  
  if (sspeede > 95 || sspeede < 85)servoe.write(sspeede);
  else servoe.write(90);
  if (sspeedd > 95 || sspeedd < 85)servod.write(sspeedd);
  else servod.write(90);


}

