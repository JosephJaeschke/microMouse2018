#include "mapAndSolve.h"
#include "Sensor.h"
#include "pid.h"

#define AIN1 8 //right motor is A
#define AIN2 5
#define PWMA A6
#define STBY 14
#define BIN1 7  //left motor is B
#define BIN2 6
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

Sensor left(IRL,160); //second param is threshold (change in setup() too)
Sensor right(IRR,160);
Sensor front(IRF,140);

short blocks=0;//how many spaces traveled

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

float distance()
{
  float distR=abs((float)rightCount*CIRC/TICKSPROT);
  float distL=abs((float)leftCount*CIRC/TICKSPROT);
  return ((distR+distL)/2)/10;

}

void moveOne()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  while(distance()<17.0)
  {
    short error=leftCount-rightCount;
    float diff=pid.compute(error);
    int adjust=SPEED-diff;
    adjust=constrain(adjust,0,255);
    analogWrite(PWMB,adjust);
    delay(10);
  }
  rightCount=0;
  leftCount=0;
  digitalWrite(STBY,LOW);
}

void turnCW()
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  delay(420);//experimental
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
  delay(390);//experimental
  digitalWrite(STBY,LOW);
  rightCount=0;
  leftCount=0;
}


void setSpace(short row,short col)
{
  int i;
  for(i=0;i<10;i++)
  {
    front.sett(analogRead(front.pin));
    left.sett(analogRead(left.pin));
    right.sett(analogRead(right.pin));
    delay(10);
  }
  byte fwall=0;
  byte rwall=0;
  byte lwall=0;
  if(front.DEMA>front.thresholdd)
  {
    fwall=1;
  }
  if(left.DEMA>left.thresholdd)
  {
    lwall=1;
  }
  if(right.DEMA>right.thresholdd)
  {
    rwall=1;
  }
  if(fwall&&grid[row][col].visited==0)
  {
    if(facing=='u')
    {
      grid[row][col].up=1;
    }
    else if(facing=='r')
    {
      grid[row][col].right=1;
    }
    else if(facing=='d')
    {
      grid[row][col].down=1;
    }
    else
    {
      grid[row][col].left=1;
    }
  }
  if(lwall&&grid[row][col].visited==0)
  {
    if(facing=='u')
    {
      grid[row][col].left=1;
    }
    else if(facing=='r')
    {
      grid[row][col].up=1;   
    }
    else if(facing=='d')
    {
      grid[row][col].right=1;
    }
    else
    {
      grid[row][col].down=1;
    }
  }
  if(rwall&&grid[row][col].visited==0)
  {
    if(facing=='u')
    {
      grid[row][col].right=1;
    }
    else if(facing=='r')
    {
      grid[row][col].down=1;
    }
    else if(facing=='d')
    {
      grid[row][col].left=1;
    }
    else
    {
      grid[row][col].up=1;
    }
  }
  if(rwall&&lwall&&blocks>=10)
  {
   //ir error corection code
   blocks=0;
   float error;
   do
   {
      error=left.DEMA-right.DEMA;
      if(error<0)
      {
       //speed up left motor
      
      }
      else if(error>0)
      {
        //slow down left motor
      
      }
   }while(abs(error)>30);
  }
  blocks++;
}

void setup()
{
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
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMA,SPEED);
  analogWrite(PWMB,SPEED);
  digitalWrite(STBY,LOW);
  pid.setPID(0.58,0.05,0.55);
  left.initS(IRL,160);
  right.initS(IRR,160);
  front.initS(IRF,140);
  attachInterrupt(digitalPinToInterrupt(LEOA),leftEncoderEvent,CHANGE);
  attachInterrupt(digitalPinToInterrupt(REOA),rightEncoderEvent,CHANGE);
  return;
}

void loop()
{
  setSpace(0,0);
  inity();
  dfsR(0,0);
  resett();
  buildPath(astar());
  return;
}
