#include "pid.h"

#define AIN1 8 //right motor is A
#define AIN2 5
#define PWMA A6
#define STBY 14
#define BIN2 6  //left motor is B
#define BIN1 7
#define PWMB A7
#define REOA 12 //right encoder out A
#define REOB 11 //right encoder out B
#define IRF A9  //front IR sensor
#define IRL A3
#define IRR A4 
#define LEOA 9 //left encoder out A
#define LEOB 10//left encoder out B

#define CIRC 3.14159265359*38.5 //from last year
#define TICKSPROT 174 //ticks per rotation (from last year)
#define SPEED 40

PID pid=PID(2.0,5.0,3.0);
volatile int leftCount=0,rightCount=0;
int prevR=0,prevL;

float distance()
{
  float distR=abs((float)(rightCount-prevR)*CIRC/TICKSPROT);
  float distL=abs((float)(leftCount-prevL)*CIRC/TICKSPROT);
  return ((distR+distL)/2)/10;

}

void moveOne()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  int timeNow=millis();
  while((millis()-timeNow)<1000)
  {
    Serial.print("IN\n");
    short error=leftCount-rightCount;
    float diff=pid.compute(error);
    int adjust=SPEED-diff;
    adjust=constrain(adjust,0,255);
    analogWrite(PWMB,adjust);
    delay(10);
  }
  digitalWrite(STBY,LOW);
  prevR=rightCount;
  prevL=leftCount;
}

void turnCW()
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  rightCount=0;
  leftCount=0;
  while(rightCount>-90);
  {
    //spin
  }
  digitalWrite(STBY,LOW);
  rightCount=0;
  leftCount=0;
}

void turnCCW()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  digitalWrite(STBY,HIGH);
  rightCount=0;
  leftCount=0;
  while(rightCount<110)
  {
    //spin
  }
  digitalWrite(STBY,LOW);
  rightCount=0;
  leftCount=0;
}

///////////////////////////////////////////
void leftEncoderEvent() {
  //Serial.printf("YO\n");
  if (digitalRead(LEOA) == HIGH) {
    if (digitalRead(LEOB) == LOW) {
      leftCount++;
    } else {
      leftCount--;
    }
  } else {
    if (digitalRead(LEOB) == LOW) {
      leftCount--;
    } else {
      leftCount++;
    }
  }
}

void rightEncoderEvent() {
  //rightCount=rightCount*-1;
  if (digitalRead(REOA) == HIGH) {
    if (digitalRead(REOB) == LOW) {
      rightCount++;
    } else {
      rightCount--;
    }
  } else {
    if (digitalRead(REOB) == LOW) {
      rightCount--;
    } else {
      rightCount++;
    }
  }
  //rightCount=rightCount*-1;

}
////////////////////////////////////////////

void setup() 
{
  pid.setPID(2.5,0.1,0.2); 
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(REOA,INPUT);
  pinMode(REOB,INPUT);
  pinMode(LEOA,INPUT);
  pinMode(LEOB,INPUT);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMA,SPEED);
  analogWrite(PWMB,SPEED);
  digitalWrite(STBY,LOW);

  attachInterrupt(digitalPinToInterrupt(LEOA),leftEncoderEvent,CHANGE);
  attachInterrupt(digitalPinToInterrupt(REOA),rightEncoderEvent,CHANGE);
}

void loop()
{
  //diagnose encoders
  Serial.printf("[ %d , %d ]\n",leftCount,rightCount);
  delay(500);
  /*
  moveOne();
  turnCCW();
  turnCCW();
  delay(1000);
  moveOne();
  turnCW();
  turnCW();
  delay(1000);
  */
}

