#define IR A0
#define A 0.0001
#define B -0.0695
#define C 16.4856

//0.0013675  -0.1107223   1.8410242

#include "mapAndSolve.h"

float dist[100];
int dSum=0;
float dAvg=0;
int d=0;

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
  float temp=dist[d%100];
  float curr=analogRead(IR);
  dist[d%100]=curr;
  dSum+=-temp+curr;
  d++;
  
  return dAvg=dSum/100;
//   dist[d]=input;
//   if(d==49)
//   {
//     d=0;
//   }
//   else
//   {
//     d++;
//   }
   
}

float analogToDist()
{
 float val=readIR();
 return A*val*val+B*val+C;
}

void setSpace(short r,short c)
{
   return; 
}

void setup()
{
  pinMode(A0,INPUT);
  return;
}

void loop()
{
  readIR();
//  inity();
//  dfsR(0,0);
//  reset();
//  buildPath(astar());
//  return;
}
