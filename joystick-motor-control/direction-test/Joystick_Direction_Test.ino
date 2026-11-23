void setup() {
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);   // D13 now gives 3.3V to the joystick

Serial.begin(115200);

}

void loop() {
int x = analogRead(34);


if (x >= 1635 && x <= 2035){
  Serial.println("STOP");
}
if (x>2035){
  Serial.println("RIGHT");
}
if (x<1635){
  Serial.println("LEFT");
}

delay(200);
}
