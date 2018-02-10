#define SIZE 50

typedef struct _Sensor
{
	byte pin;
	float dist[SIZE];
	int dSum;
	float dAvg;
	byte dIndex;
}Sensor;
