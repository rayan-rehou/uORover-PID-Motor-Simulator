const int IN1 = 26;
const int IN2 = 25;
const int IN3 = 33;
const int IN4 = 27;

// which coils are ON (1) or OFF (0) at each of the 4 clicks        (the table is in the datasheet, its just how it is)
const int SEQ[4][4] = {
  {1, 1, 0, 0},   // click 0
  {0, 1, 1, 0},   // click 1
  {0, 0, 1, 1},   // click 2
  {1, 0, 0, 1}    // click 3
};

const long LIMIT = 1024;       // 1024 clicks = 180 degrees, the furthest it can go each way

int step = 0;   // which row we're on
long position = 0;             // total clicks from the start (+ right, - left)
unsigned long lastPrint = 0;   // last time we printed the angle

// turn on the coils for the current row
void writeStep() {
  digitalWrite(IN1, SEQ[step][0]);
  digitalWrite(IN2, SEQ[step][1]);
  digitalWrite(IN3, SEQ[step][2]);
  digitalWrite(IN4, SEQ[step][3]);
}
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   // joystick power (3.3V)

  pinMode(32, INPUT_PULLUP);   // joystick button (HIGH = not pressed, LOW = pressed)

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);

}

void loop() {
  int x = analogRead(34);

  if (digitalRead(32) == LOW) {   // button pressed
    position = 0;                 // the current spot becomes the new zero
    Serial.println("Zero set");
    delay(300);                   // wait so one click isn't counted many times
  }

  if (x > 2035 && position < LIMIT) {            // RIGHT        // only if not at +180
    step = step + 1;
    if (step > 3) step = 0;   // after row 3, go back to row 0
    writeStep();
    position = position + 1;    // one click right
    int wait = map(x, 2035, 4095, 20, 2);     // x = joystick, 2035 = barely right, 4095 = full right, 20 = slow wait, 2 = fast wait
    delay(wait);
  }
  else if (x < 1635 && position > -LIMIT) {       // LEFT        // only if not at -180
    step = step - 1;
    if (step < 0) step = 3;   // before row 0, go back to row 3
    writeStep();
    position = position - 1;   // one click left
    int wait = map(x, 1635, 0, 20, 2);       // x = joystick, 1635 = barely left, 0 = full left, 20 = slow wait, 2 = fast wait
    delay(wait);
  }
  else {          // STOP
    delay(3);
  }


if (millis() - lastPrint > 200) {
    float angle = position * 360.0 / 2048;   // 2048 clicks = 360 degrees
    Serial.println(angle);
    lastPrint = millis();
  }
}
