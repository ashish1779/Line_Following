int prev_err =0 , err , derr=0;
int kp = 25;
int kd = 30;
int corr;
int l1=80,r1=80;
int l,r;
int mrf=33,mrb=32,mlf=39,mlb=38;//mrf = dirction,mrb = break;
int pwm1=6,pwm2=7;
int data;

void setup() 
{
  pinMode(mrf,OUTPUT);
  pinMode(mrb,OUTPUT);
  pinMode(mlf,OUTPUT);
  pinMode(mlb,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  Serial.begin(9600);
}

void pid()
{
  derr = err - prev_err;
  prev_err = err;
  corr = kp * err + kd * derr;
  /*Serial.print("ERR");
  Serial.print(err);
  Serial.print("DERR");
  Serial.print(derr);*/
}

void forward()
{
  digitalWrite(mrf,HIGH);
  digitalWrite(mrb,LOW);
  digitalWrite(mlf,HIGH);
  digitalWrite(mlb,LOW);
  analogWrite(pwm1,r);
  analogWrite(pwm2,l);
}
/*
void backward()
{
  digitalWrite(mrf,LOW);
  digitalWrite(mrb,LOW);
  digitalWrite(mlf,LOW);
  digitalWrite(mlb,LOW);
  analogWrite(pwm1,r);
  analogWrite(pwm2,l);
}

void left()
{
  digitalWrite(mrf,HIGH);
  digitalWrite(mrb,LOW);
  digitalWrite(mlf,LOW);
  digitalWrite(mlb,LOW);
  l=l1;
  r=r1;
  analogWrite(pwm1,r);
  analogWrite(pwm2,l);
}

void right()
{
  digitalWrite(mrf,LOW);
  digitalWrite(mrb,LOW);
  digitalWrite(mlf,HIGH);
  digitalWrite(mlb,LOW);
  l=l1;
  r=r1;
  analogWrite(pwm1,r);
  analogWrite(pwm2,l);
}

void pause()
{
  digitalWrite(mrb,HIGH);
  digitalWrite(mlb,HIGH);
}
*/  
void drive()
{
  l = l1 + corr;
  r = r1 - corr;
  if(r<0) 
    {r=0;}
  if(r>255) 
    {r=255;}
  if(l<0) 
    {l=0;}
  if(l>255) 
    {l=255;}
        
  forward();
  
  Serial.print("L = ");
  Serial.print(l);
  
  Serial.print(" R = ");
  Serial.println(r);
}

void linefollow()
{
  pid();
  drive();
}


void loop()
{ while (Serial.available())
  {
    data = Serial.read();
  }
  Serial.print("Recived Data is ");
  Serial.println(data);
  err = data; 
  linefollow();
//  Serial.print("Corre = ");
//  Serial.println(corr);
//  delay(100);
}
