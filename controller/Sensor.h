class Sensor
{
  public:
  byte pin;
  float ema_a;
  float ema_ema;
  float ema;
  short threshold;
  float DEMA;
  float curr;
  Sensor(byte p,short t)
  {
    pin=p;
    ema=0;
    ema_a=0.06;
    ema_ema=0;
    threshold=t;
    DEMA=0;
    curr=0;
  }
  void set()
  {
    ema_func(curr);
    ema_ema_func();
    DEMA=2*ema-ema_ema;
  }
  private:
  void ema_func(short curr)
  {
    ema=(ema_a*curr+(1-ema_a)*ema);
  }
  void ema_ema_func()
  {
    ema_ema=(ema_a*ema+(1-ema_a)*ema_ema);
  }
	
};
