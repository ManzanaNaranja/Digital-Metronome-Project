const int buzzer = 9;
const int signal  = 10;
bool isHigh = false;


void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(signal, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  Serial.println(digitalRead(signal));
  if (digitalRead(signal) == HIGH && isHigh == false){
    tone(buzzer, 2000); // Send 1KHz sound signal...
    delay(50);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    isHigh = true;
  }
  if (digitalRead(signal) == LOW){
    isHigh = false;
  }
}
