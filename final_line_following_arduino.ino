/* Line Follow using Image processing
  Arduino code
  Data getting from python script
  Processed in arduino for PID
  //Ashish_Anand
*/

int prev_err =0 , err , derr=0,corr; //PID Variable
int kp = 2; //PID constant
int kd = 2; //PID constant

int mls=80,mrs=80;
int lspeed,rspeed;

int mrpwm,mlpwm;
int mrf=24, mrb=25, mlf=22, mlb=23; //Define motor dir pins
int mrp=6,mlp=7; //Define PWM pins

int data;

void setup() 
{
  pinMode(mrf,OUTPUT);
  pinMode(mrb,OUTPUT);
  pinMode(mlf,OUTPUT);
  pinMode(mlb,OUTPUT);
  pinMode(mrp,OUTPUT);
  pinMode(mlp,OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready");
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

void drive()
{     mrpwm=mrs+corr;
      mlpwm=mls-corr;
  
      
      if(mlpwm<0) 
      {
        mlpwm=(-1)*mlpwm;
        
        digitalWrite(mlf,LOW);
        digitalWrite(mrf,HIGH);
        digitalWrite(mlb,HIGH);
        digitalWrite(mrb,LOW);
      
        //analogWrite(mlp,mlpwm);
        //analogWrite(mrp,mrpwm);
      }
      
      if(mrpwm<0) 
      {
        mrpwm=(-1)*mrpwm;
      
        //if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
        digitalWrite(mlf,HIGH);
        digitalWrite(mrb,HIGH);
        digitalWrite(mlb,LOW);
      
        //analogWrite(mlp,mlpwm);
        //analogWrite(mrp,mrpwm);
      }
      
      
      if(mlpwm>0 && mrpwm>0)
      {
        
      //if(mlpwm>120) mlpwm=120;
      //if(mrpwm>120) mrpwm=120;
      
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      //analogWrite(mlp,mlpwm);
      //analogWrite(mrp,mrpwm);
      }
   
   
   if(mlpwm>254) mlpwm=180;
   if(mrpwm>254) mrpwm=180;
   
    
    lspeed=map(mlpwm,0,254,120,180);
    rspeed=map(mrpwm,0,254,120,180);
    
    analogWrite(mlp,lspeed);
    analogWrite(mrp,rspeed);
      
  Serial.print("L = ");
  Serial.print(lspeed);
  
  Serial.print(" R = ");
  Serial.println(rspeed);    
      
}

void linefollow()
{
  pid();
  drive();
}

void loop()
{ 
  String inByte = " ";
  if(Serial.available())
  {
   String inByte = Serial.readString();
   data = inByte.toInt();
   Serial.println(data);
   err = data; 
   linefollow();
  }
  delay(100);
  

}
