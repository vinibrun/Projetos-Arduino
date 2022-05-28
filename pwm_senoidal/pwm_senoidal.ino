#define pwmPin1 5
#define pwmPin2 6

const float pi = 3.14;

void pwm(int tmicros, int tmilis) {
  float i = 0.0;
  while (i < pi - 0.05) {
    analogWrite(pwmPin1, 255 * sin(i));
    i += pi / 16.0;
    delay(tmilis);
    delayMicroseconds(tmicros);
  }
  digitalWrite(pwmPin1, LOW);
  delayMicroseconds(1000);
  i = 0.0;
  while (i < pi - 0.05) {
    analogWrite(pwmPin2, 255 * sin(i));
    i += pi / 16.0;
    delay(tmilis);
    delayMicroseconds(tmicros);
  }
  digitalWrite(pwmPin2, LOW);
  delayMicroseconds(1000);
}

void setup() {
  TCCR0B = TCCR0B & 0b11111000 | 0X01; //Temporizador 0 (PWM pinos 5 & 6)
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(3, LOW);
}

void loop() {
  /*
    float j;
    for (j = 300.0; j > 100; j -= j/4)
    pwm(0, (int)j);
    for (j = 100.0; j > 50; j -= j/8)
    pwm(0, (int)j);
    for (j = 50.0; j > 0; j -= j/16)
    pwm(0, (int)j);
  */
  pwm(10, 0);
}
