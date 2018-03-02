#include "mapAndSolve.h"
#include "Sensor.h"
Sensor left(1,160);
Sensor right(2,160);
Sensor front(0,160);

void moveOne(short row,short col)
{
  //digitalWrite(STBY,HIGH);
  //...
  //digitalWrite(STBY,LOW);
  readIR(row,col);
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

void readIR(short row,short col)
{
  front.curr=analogRead(front.pin);
  left.curr=analogRead(left.pin);
  right.curr=analogRead(right.pin);
  front.set();
  left.set();
  right.set();
  if(front.DEMA>front.threshold&&grid[row][col].visited==0)
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
  if(left.DEMA>left.threshold&&grid[row][col].visited==0)
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
  if(right.DEMA>right.threshold&&grid[row][col].visited==0)
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
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);

  return;
}

void loop()
{
  readIR(0,0);
//  inity();
//  dfsR(0,0);
//  reset();
//  buildPath(astar());
//  return;
}
