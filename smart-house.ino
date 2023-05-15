#include <Servo.h>
int smActivePin=8; //step motor active pin
String btState; //bluetooth state
Servo m1;
Servo m2;

void setup() {
  //Attaching servo motors to pins.
  m1.attach(12);
  m2.attach(13);

  //LEDs
  pinMode(2,OUTPUT); //Room-1 Light
  pinMode(3,OUTPUT); //Room-2 Light
  pinMode(4,OUTPUT); //Saloon Light
  pinMode(5,OUTPUT); //Outdoor Light
  pinMode(6,OUTPUT); //Outdoor Light
  pinMode(7,OUTPUT); //Outdoor Light

  //Communication speed
  Serial.begin(9600);

  //LED's Initial States
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);

  //Step Motor Pins
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
    while(Serial.available() > 0){
      btState = Serial.readString();
      if(btState == "interiorLights:on"){
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,HIGH);
      } else if(btState == "interiorLights:off"){
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
      } else if(btState == "outdoorLights:on"){
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
      } else if(btState == "outdoorLights:off"){
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
      } else if(btState == "room1:on"){
        digitalWrite(2,HIGH);
      } else if(btState == "room1:off"){
        digitalWrite(2,LOW);
      } else if(btState == "room2:on"){
        digitalWrite(3,HIGH);
      } else if(btState == "room2:off"){
        digitalWrite(3,LOW);
      } else if(btState == "saloon:on"){
        digitalWrite(4,HIGH);
      } else if(btState == "saloon:off"){
        digitalWrite(4,LOW);
      }else if(btState == "blankets:on"){
        m1.write(90);
        delay(50);
        m2.write(90);
        delay(50);
      } else if(btState == "blankets:off"){
        m1.write(0);
        delay(50);
        m2.write(0);
        delay(50);
      } else if(btState == "garage:on"){
        turnStepMotorR(500);
      } else if(btState == "garage:off"){
        turnStepMotorL(500);
      } else {
        btState = "";
      }
  }
  delay(100);
}
void turnStepMotorL(int step){
  for(int i = 0; i < step; i++){
    digitalWrite(smActivePin,HIGH);
    delay(2);
    digitalWrite(smActivePin,LOW);
    increaseSmActivePin();
  }
}

void turnStepMotorR(int step){
  for(int i = 0; i < step; i++){
    digitalWrite(smActivePin,HIGH);
    delay(2);
    digitalWrite(smActivePin,LOW);
    decreaseSmActivePin();
  }
}

void increaseSmActivePin(){
  smActivePin = smActivePin + 1;
  if(smActivePin == 12){
    smActivePin = 8;
  }
}

void decreaseSmActivePin(){
  smActivePin = smActivePin - 1;
  if(smActivePin == 7){
    smActivePin = 11;
  }
}