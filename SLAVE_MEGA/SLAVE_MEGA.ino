#include<SPI.h>
#include"Directions.h"
#define ppr_pin 46
#define feedback_pin A3
#define DCV 42


byte button;
int pwm = 150;
int throwingPressure = 800; int ppr_pwm = 255;

///// Change the number of motors in
Motor motor1(11, 9);
Motor motor2(8, 10);
Motor motor4(3, 5, 4);
Motor motor3(22, 6, 24);

Direction bot(motor1, motor2, motor3, motor4);


void setup() {
  Serial.begin (115200);
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE); // enable spi module
  SPI.attachInterrupt(); // turn on interrupt
  pinMode(ppr_pin, OUTPUT);
  pinMode(DCV, OUTPUT);
}

ISR(SPI_STC_vect) {
  if (SPDR < 100) {
    button = SPDR;
  } else {
    SPDR = 0;
    button = 0;
  }
}


void loop() {
  //Throwing arrow

  while(button == 50) {
    analogWrite(ppr_pin, ppr_pwm);
    while(button == 50 && analogRead(feedback_pin) < throwingPressure);
    while(button == 50 && analogRead(feedback_pin) > throwingPressure) {
      digitalWrite(DCV, HIGH);
    }
  }
  digitalWrite(DCV, LOW);
  
  if (button == 1) {
    bot.forward(pwm);
    Serial.println("Forward");
  }
  else if (button == 3) {
    bot.backward(pwm);
    Serial.println("Backward");
  }
  else if (button == 5) {
    bot.left(pwm);
    Serial.println("L");
  }
  else if (button == 7) {
    bot.right(pwm);
    Serial.println("R");
  }
  else if (button == 2) {
    bot.up_left(pwm);
    Serial.println("UL");
  }
  else if (button == 4)
  {
    bot.up_right(pwm);
    Serial.println("UR");
  }
  else if (button == 6)
  {
    bot.down_left(pwm);
    Serial.println("DL");
  }
  else if (button == 8)
  {
    bot.down_right(pwm);
    Serial.println("DR");
  }
  else if (button == 16)
  {
    bot.clockwise(pwm);
    Serial.println("CL");
  }
  else if (button == 17)
  {
    bot.antiClockwise(pwm);
    Serial.println("ACL");
  }
  else if (button == 9) { 
    pwm = 200;
    Serial.println("PWM 255");
  }
  else if (button == 11) {
    pwm = 100;
    Serial.println("PWM 100");
  } 
  else if(button == 52) {
    throwingPressure -= 20;
    Serial.println("Decreased pressure required to throw the arrow");
  } 
  else if(button == 53) {
    throwingPressure += 20;
    Serial.println("Increased pressure required to throw the arrow");
  }
  else {
    bot.brake();
  }

}
