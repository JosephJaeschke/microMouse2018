class PID
{
	public:
	void PID(float p,float i,float d)
	{
		Kp=p;
		Ki=i;
		Kd=d;
		return;
	}
	void set(float p,float i,float d)
	{
		Kp=p;
		Ki=i;
		Kd=d;
		return;
	}
	void compute()
	{
		unsigned long now=millis();
		float timeChg=(float)now-(float)last;
		float err=setPt-input;
		errSum+=err;
		float errD=(err-lastErr)/timeChg;
		output=Kp*err+Ki*errSum+Kd*errD;
		lastErr=err;
		last=now;

	}

	private:
	float Kp,Ki,Kd;
	float errSum,lastErr;
	float input,output,setPt;
	unsigned long last;

}
