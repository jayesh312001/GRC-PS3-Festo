#include<SPI.h>
#include<Ps3Controller.h>

SPIClass * vspi = NULL;

void setup() {
//  digitalWrite(4, HIGH);
  SPI.begin();
  vspi = new SPIClass(VSPI);          //initialise pointer
  vspi->begin(); //set baud rate to 115200 for usart
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  Ps3.begin("33:33:33:33:33:33");
  Ps3.attach(notify);
  Serial.println("Ready to connect");
}

void notify() {

  if (Ps3.isConnected()) {
    if (Ps3.data.button.ps) {
      Serial.println("Should Disconnect from ESP");
//      ESP.restart();
    }
    else if (Ps3.data.button.up) {
      Serial.println("UP");
      sendData(1);
    }
    else if (Ps3.data.button.down) {
      Serial.println("DOWN");
      sendData(3);;
    }
    else if (Ps3.data.button.left) {
      Serial.println("Left");
      sendData(5);
    }
    else if (Ps3.data.button.right) {
      Serial.println("Right");
      sendData(7);
    }
    else if ( Ps3.data.button.cross ) {
      sendData(52);
      Serial.println("Decrease throwing pressure setpoint");
    } else if ( Ps3.data.button.triangle ) {
      sendData(53);
      Serial.println("Increase throwing pressure setpoint");
    }
    else {
      sendData(99);
    }
  }
  else {
    Serial.println("Disconnected");
    sendData(125);
//    digitalWrite(4, LOW);
  }
}
void loop() {
  //  if (!Ps3.isConnected()) {
  //    Serial.println("Disconnected");
  //    sendData(125);
  //    digitalWrite(4, LOW);
  //  }
//  notify();
sendData(11);
yield();
}

void sendData(int x) {
  vspi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
  vspi->transfer(x);
  digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
}
