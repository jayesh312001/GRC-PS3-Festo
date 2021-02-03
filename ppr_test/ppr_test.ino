#define DCV 44
#define PPR_PIN 46 
#define feedback_pin A3


void setup() {
  // put your setup code here, to run once:
  pinMode(DCV, OUTPUT);
  Serial.begin(115200);
  pinMode(PPR_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PPR_PIN, 150);
  while(analogRead(feedback_pin) < 150){
    Serial.println(analogRead(feedback_pin));
    }
  digitalWrite(DCV, HIGH);
  delay(500);
  digitalWrite(DCV, LOW);
  analogWrite(PPR_PIN, 0);
  while(1);
}
