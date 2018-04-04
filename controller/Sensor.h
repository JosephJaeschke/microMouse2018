class Sensor
{
  public:
  byte pin;
  float ema_a;
  float ema_ema;
  float ema;
  short thresholdd;
  float DEMA;
  float curr;
  Sensor(byte p,short t)
  {
    pin=p;
    ema=0;
    ema_a=0.06;
    ema_ema=0;
    thresholdd=t;
    DEMA=0;
    curr=0;
  }
  void initS(byte p,short t)
  {
    pin=p;
    ema=0;
    ema_a=0.06;
    ema_ema=0;
    thresholdd=t;
    DEMA=0;
    curr=0;
  }
  void sett(float c)
  {
    //Serial.printf("[%f]",c);
    ema_func(c);
    ema_ema_func();
    DEMA=2*ema-ema_ema;
    //Serial.printf("(%f) ",DEMA);
  }
  private:
  void ema_func(float curr)
  {
    ema=(ema_a*curr+(1-ema_a)*ema);
  }
  void ema_ema_func()
  {
    ema_ema=(ema_a*ema+(1-ema_a)*ema_ema);
  }
	
};
