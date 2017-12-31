#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

//Motor1 is controlled by IN1 and IN2
//Motor2 is controlled by IN3 and IN4
const int IN1 = 6;
const int IN2 = 5;
const int IN3 = 4;
const int IN4 = 3;

void setup() {
      pinMode(IN1,OUTPUT);
      pinMode(IN2,OUTPUT);
      pinMode(IN3,OUTPUT);
      pinMode(IN4,OUTPUT);
      Serial.begin(9600);
      
      radio.begin();
      Serial.println("checking if chip connected");
      bool check = radio.isChipConnected();
      Serial.print("check-");
      Serial.println(check);
      
      radio.openReadingPipe(0, address);
      radio.setPALevel(RF24_PA_MIN);
      radio.startListening();
}
void loop() {
      if (radio.available()) {
            int message[4];
            radio.read(&message, sizeof(message));
            int i;
            for (i = 0; i < 4; i = i + 1) {
                  Serial.print(message[i]);
            }
            Serial.println();
            int sum = message[0]+message[1]+message[2]+message[3];
            if (sum==4) {
                  //stop
                  digitalWrite(IN1,LOW);
                  digitalWrite(IN2,LOW);
                  digitalWrite(IN3,LOW);
                  digitalWrite(IN4,LOW);
                  Serial.println("LLLL");                  
            }
            if (sum==3) {
                  if (message[0]==0 && message[1]==1 && message[2]==1 && message[3]==1) {
                        //move forward
                        digitalWrite(IN1,HIGH);
                        digitalWrite(IN2,LOW);
                        digitalWrite(IN3,LOW);
                        digitalWrite(IN4,HIGH);
                        Serial.println("HLLH");
                  }
                  if (message[0]==1 && message[1]==0 && message[2]==1 && message[3]==1) {
                        //move backward
                        digitalWrite(IN1,LOW);
                        digitalWrite(IN2,HIGH);
                        digitalWrite(IN3,HIGH);
                        digitalWrite(IN4,LOW);
                        Serial.println("LHHL");
                  }
                  if (message[0]==1 && message[1]==1 && message[2]==0 && message[3]==1) {
                        //move forward
                        digitalWrite(IN1,LOW);
                        digitalWrite(IN2,LOW);
                        digitalWrite(IN3,LOW);
                        digitalWrite(IN4,HIGH);
                        Serial.println("LLLH");
                  }
                  if (message[0]==1 && message[1]==1 && message[2]==1 && message[3]==0) {
                        //move left
                        digitalWrite(IN1,HIGH);
                        digitalWrite(IN2,LOW);
                        digitalWrite(IN3,LOW);
                        digitalWrite(IN4,LOW);
                        Serial.println("HLLL");
                  }
            }
            if (sum<=2) {
                  //stop
                  digitalWrite(IN1,LOW);
                  digitalWrite(IN2,LOW);
                  digitalWrite(IN3,LOW);
                  digitalWrite(IN4,LOW);
                  Serial.println("LLLL");
            }
      }
}
