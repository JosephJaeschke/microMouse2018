#define PWMA 10
#define AIN2 3
#define AIN1 2
#define PWMB 11
#define BIN2 5
#define BIN1 4
#define STBY 6

#define Ab 12
#define Aa 13
#define Ba 8
#define Bb 9

int i=0;
int AaEnc=0;
int AbEnc=0;
int BaEnc=0;
int BbEnc=0;

void setup() 
{
  Serial.begin(9600);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(Ab,INPUT);
  pinMode(Aa,INPUT);
  pinMode(Bb,INPUT);
  pinMode(Ba,INPUT);
  digitalWrite(STBY,LOW);
  analogWrite(PWMA,57); //55,56,57 works
  analogWrite(PWMB,57); //55,56,57 works
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);

}

void loop()
{
}
