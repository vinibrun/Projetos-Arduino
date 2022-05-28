#include <Servo.h>

Servo myservo0;
Servo myservo1;

int luz = 0;  // analog pin used to connect the potentiometer
int val, val2;    // variable to read the value from the analog pin
int atual, i;
void setup() {
  myservo0.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(10);  // attaches the servo on pin 9 to the servo object
  delay(5000);
  myservo0.write(0);
  myservo1.write(180);
  delay(400);
}

void loop() {
  val = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
  val2 = analogRead(A1);            // reads the value of the potentiometer (value between 0 and 1023)
  if (val > 600 || val2 > 600) {
    myservo0.write(180);
    myservo1.write(180);  // sets the servo position according to the scaled value
    delay(1000);
    myservo0.write(0);
    myservo1.write(180);  // sets the servo position according to the scaled value
    atual = random(1, 10);
    for (i = 0; i < atual; i++)
      delay(150);
  }
  myservo0.write(0);
  myservo1.write(0);  // sets the servo position according to the scaled valu
  delay(15);                           // waits for the servo to get there
}

