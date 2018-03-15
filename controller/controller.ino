#include "mapAndSolve.h"
#include "Sensor.h"
Sensor left(A3,160); //second param is threshold (change in setup() too)
Sensor right(A4,160);
Sensor front(A9,160);

void moveOne()
{
  //digitalWrite(STBY,HIGH);
  //...
  //digitalWrite(STBY,LOW);
  return;
}

void turnCW()
{
  return;
}

void turnCCW()
{
  return;
}

void setSpace(short row,short col)
{
  front.sett(analogRead(front.pin));
  left.sett(analogRead(left.pin));
  right.sett(analogRead(right.pin));
  if(front.DEMA>front.thresholdd&&grid[row][col].visited==0)
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
  if(left.DEMA>left.thresholdd&&grid[row][col].visited==0)
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
  if(right.DEMA>right.thresholdd&&grid[row][col].visited==0)
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
}

void setup()
{
  Serial.begin(9600);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A9,INPUT);
  left.initS(A3,160);
  right.initS(A4,160);
  front.initS(A9,160);
  return;
}

void readIR()
{
  left.sett(analogRead(left.pin));
  front.sett(analogRead(front.pin));
  right.sett(analogRead(right.pin));
  if(left.DEMA>left.thresholdd)
  {

    Serial.printf("1 ");
    
  }
  else
  {
    Serial.printf("0 ");
  }
  if(front.DEMA>front.thresholdd)
  {
    Serial.printf("1 ");
  }
  else
  {
    Serial.printf("0 ");
  }
  if(right.DEMA>right.thresholdd)
  {
    Serial.printf("1 \n");
  }
  else
  {
    Serial.printf("0\n");
  }
}

void loop()
{
  readIR();
  delay(250);
//  setSpace(0,0);
//  inity();
//  dfsR(0,0);
//  reset();
//  buildPath(astar());
//  return;
}
