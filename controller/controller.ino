#define IR A0
#define FILTER 100
#define A 0.0001
#define B -0.0695
#define C 16.4856

//0.0013675  -0.1107223   1.8410242

#include "mapAndSolve.h"
#include "Sensor.h"

Sensor left,right,front;

void moveOne()
{
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

float readIR()
{
//  float temp=dist[d%FILTER];
//  float curr=analogRead(IR);
//  dist[d%FILTER]=curr;
//  dSum+=temp+curr;
//  d++;
//  return dAvg=dSum/FILTER;
   
}

float analogToDist()
{
 float i=readIR();
 return (((((-0.0000000000416*i + 0.0000000938508)*i - 0.0000820544671)*i + 0.0350213702595)*i - 7.4822471184731)*i + 699.9053694888168);
}

void setSpace(short r,short c)
{
  
   return; 
}

void setup()
{
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  front.pin=0;
  front.dSum=0;
  front.dAvg=0;
  front.dIndex=0;
  right.pin=1;
  right.dSum=0;
  right.dAvg=0;
  right.dIndex=0;
  left.pin=2;
  left.dSum=0;
  left.dAvg=0;
  left.dIndex=0;
  return;
  
}

void loop()
{
  readIR();
  delay(28);
//  inity();
//  dfsR(0,0);
//  reset();
//  buildPath(astar());
//  return;
}
