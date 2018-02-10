#define IR A0
#define FILTER 100
#define A 0.0001
#define B -0.0695
#define C 16.4856

//0.0013675  -0.1107223   1.8410242

#include "mapAndSolve.h"
#include "Sensor.h"
Sensor left,right,front;

float dist[FILTER];
float dSum=0;
float dAvg=0;
int d=0;

float ema_a=0.06;
int ema_ema =0;
int ema=0; 


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
  int curr=analogRead(IR);
  ema=ema_func(ema_a,curr,ema);
  ema_ema=ema_func(ema_a,ema,ema_ema);
  int DEMA=2*ema-ema_ema;
  
//  float temp=dist[d%FILTER];
//  float curr=analogRead(IR);
//  dist[d%FILTER]=curr;
//  dSum+=-temp+curr;
//  d++;
//  dAvg=dSum/FILTER;
  Serial.print(DEMA);
  Serial.print("\n");
   
}

float ema_func(float a,int now,int stored)
{
  return (int)(a*now+(1-a)*stored);
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
  Serial.begin(9600);
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
  delay(68);
//  inity();
//  dfsR(0,0);
//  reset();
//  buildPath(astar());
//  return;
}
