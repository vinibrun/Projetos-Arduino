

void setup() {
  // put your setup code here, to run once:
  analogWriteResolution(12);
}

void loop() {
  int i;
  for (i = 0; i < 4095; i++) {
    analogWrite(DAC0, i);
    analogWrite(DAC1, 0);
  }
  for (i = 0; i < 4095; i++) {
    analogWrite(DAC0, 4095);
    analogWrite(DAC1, i);
  }
  for (i = 4095; i > 0; i--) {
    analogWrite(DAC0, i);
    analogWrite(DAC1, 4095);
  }
  for (i = 4095; i > 0; i--) {
    analogWrite(DAC0, 0);
    analogWrite(DAC1, i);
  }
}
