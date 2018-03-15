#include "pid.h"

#define AIN1 2 //right motor is A
#define AIN2 1
#define PWMA 4
#define STBY 5
#define BIN1 6  //left motor is B
#define BIN2 7
#define PWMB 3
#define REOA 11 //right encoder out A
#define REOB 10 //right encoder out B
#define IRF 16  //front IR sensor
#define IRL 17
#define IRR 18 
#define LEOA 8 //left encoder out A
#define LEOB 9//left encoder out B

#define CIRC 3.14159265359*40.12 //from last year
#define TICKSPROT 615 //ticks per rotation (from last year)
#define SPEED 40

PID pid=PID(2.0,5.0,3.0);
volatile int leftCount=0,rightCount=0;

float distance()
{
  float distR=abs((float)rightCount*CIRC/TICKSPROT);
  float distL=abs((float)leftCount*CIRC/TICKSPROT);
  return ((distR+distL)/2)/10;

}

void travel()
{
  while(1)
  {
    //digitalWrite(STBY,LOW);
    short error=leftCount-rightCount;
    Serial.printf(">e:%d\n",error);
    float diff=pid.compute(error);
    Serial.printf(">D:%d\n",diff);
    int adjust=SPEED-diff;
    adjust=constrain(adjust,0,255);
    Serial.printf(">d:%d\n---\n",adjust);
    analogWrite(PWMB,adjust);
    
    //digitalWrite(STBY,HIGH);
  }
  //digitalWrite(STBY,LOW);
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
  pid.setPID(0.5,0.02,0.321); //0.5,0.020,0.321 is quite good
  Serial.begin(9600);
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
  digitalWrite(STBY,LOW);
  analogWrite(PWMA,SPEED);
  analogWrite(PWMB,SPEED); 
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  attachInterrupt(digitalPinToInterrupt(LEOA),leftEncoderEvent,CHANGE);
  attachInterrupt(digitalPinToInterrupt(REOA),rightEncoderEvent,CHANGE);
}

void loop()
{
  travel();
  //delay(250);
  //Serial.printf("[%d,%d]\n",rightCount,leftCount);  
}

