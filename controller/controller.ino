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
#define SPEED 50

PID pid=PID(0,0,0);
PID irPID=PID(0,0,0);
volatile int leftCount=0,rightCount=0;
int prevR=0,prevL=0;
bool use_enc=true;

Sensor left(0,0); 
Sensor right(0,0);
Sensor front(0,0);

void leftEncoderEvent() 
{
  if(digitalRead(LEOA)==HIGH)
  {
    if(digitalRead(LEOB)==LOW)
    {
      leftCount++;
    }
    else
    {
      leftCount--;
    }
  } 
  else
  {
    if(digitalRead(LEOB)==LOW)
    {
      leftCount--;
    }
    else 
    {
      leftCount++;
    }
  }
}

void rightEncoderEvent() 
{
  if(digitalRead(REOA)==HIGH)
  {
    if(digitalRead(REOB)==LOW)
    {
      rightCount++;
    }
    else
    {
      rightCount--;
    }
  } 
  else
  {
    if(digitalRead(REOB)==LOW)
    {
      rightCount--;
    }
    else
    {
      rightCount++;
    }
  }
}

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
  if(use_enc)
  {
    while(distance()<17.0)
    {
      short error=leftCount-rightCount;
      float diff=pid.compute(error);
      int adjust=SPEED-diff;
      adjust=constrain(adjust,0,255);
      analogWrite(PWMB,adjust);
      delay(10);
    }
  }
  else
  {
    while(distance()<17.0)
    {
      //spin
    }
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
  while(rightCount>-100&&leftCount<100)//double check
  {
    //spin
  }
  digitalWrite(STBY,LOW);
  delay(10);
  rightCount=0;
  leftCount=0;
  prevR=0;
  prevL=0;
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
  while(rightCount<115&&leftCount>-115)//double check
  {
    //spin
  }
  digitalWrite(STBY,LOW);
  delay(10);
  rightCount=0;
  leftCount=0;
  prevR=0;
  prevL=0;
}

void setSpace(short row,short col)
{
  int i;
  for(i=0;i<20;i++)
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
  use_enc=true;
  if(rwall&&lwall)
  {
   short error=left.DEMA-right.DEMA;
   float diff=irPID.compute(error);
   int adjust=SPEED-diff;
   adjust=constrain(adjust,0,255);
   analogWrite(PWMB,adjust);
   use_enc=false;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
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
  digitalWrite(13,HIGH);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMA,SPEED);
  analogWrite(PWMB,SPEED);
  digitalWrite(STBY,LOW);
  pid.setPID(3.8,0.1,0.2);
  irPID.setPID(2.5,0.1,0.2);
  left.initS(IRL,160);
  right.initS(IRR,160);
  front.initS(IRF,140);
  attachInterrupt(digitalPinToInterrupt(LEOA),leftEncoderEvent,CHANGE);
  attachInterrupt(digitalPinToInterrupt(REOA),rightEncoderEvent,CHANGE);
}

void loop()
{
  /*
  //encoder test
  Serial.printf("[%d , %d]\n",leftCount,rightCount);
  delay(10);
  */

  //ir pid test
  setSpace(0,0);
  moveOne();
  
  /*
  //turn test
  moveOne();
  turnCCW();
  turnCCW();
  delay(500);
  moveOne();
  turnCW();
  turnCW();
  delay(500);
  */
  /*
  //real code
  setSpace(0,0);
  inity();
  dfsR(0,0);
  resett();
  buildPath(astar());
  exit(0);
 */
}
