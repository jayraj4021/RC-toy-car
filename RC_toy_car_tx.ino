#include <SPI.h>
#include <RF24.h>

RF24 radio(7,8);
const byte address[6] = "00001";

const int frontButton = 6; //pressing button moves toy car forward
const int backButton = 5;  //pressing button moves toy car backward
const int leftButton = 4;  //pressing button moves toy car to left
const int rightButton = 3; //pressing button moves toy car to right

void setup() {
      // put your setup code here, to run once:
      pinMode(frontButton,INPUT_PULLUP);
      pinMode(backButton,INPUT_PULLUP);
      pinMode(leftButton,INPUT_PULLUP);
      pinMode(rightButton,INPUT_PULLUP);
      Serial.begin(9600);

      radio.begin();
      Serial.println("checking if chip connected");
      bool check = radio.isChipConnected();
      Serial.print("check-");
      Serial.println(check);
  
      radio.openWritingPipe(address);
      radio.setPALevel(RF24_PA_HIGH);
      radio.stopListening();
}

void loop() {
      // put your main code here, to run repeatedly:
      int message[4];
      
      message[0] = digitalRead(frontButton);
      message[1] = digitalRead(backButton);
      message[2] = digitalRead(leftButton);
      message[3] = digitalRead(rightButton);
      //int i;
      //for (i = 0; i < 4; i = i + 1) {
      //      Serial.print(message[i]);
      //}
      Serial.println("Transmitted");
      radio.write(&message,sizeof(message));
      delay(100);       //You can play with this number
}
