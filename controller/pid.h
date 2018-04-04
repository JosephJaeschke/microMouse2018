class PID
{
  private:
  float Kp,Ki,Kd,outPut;
  short errSum,lastErr;
  unsigned long last;
  
	public:
	PID(float p,float i,float d)
	{
		Kp=p;
		Ki=i;
		Kd=d;
	}
 void setPID(float p,float i,float d)
 {
    Kp=p;
    Ki=i;
    Kd=d;
    return;
 }
	float compute(short err)
	{
		unsigned long now=millis();
		float timeChg=(float)now-(float)last;
		errSum+=err;
		float errD=(err-lastErr)/timeChg;
		outPut=Kp*err+Ki*errSum+Kd*errD;
		lastErr=err;
		last=now;
    return outPut;
	}
};

