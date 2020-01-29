char data;
int led1 = 13;

void setup() 
{
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
}

void loop() 
{
 
  if (Serial.available() > 0)
  {
    data = Serial.read();
  }

  if (data == 49)   //UP
  {
    digitalWrite(led1, HIGH);
    Serial.println("UP");
  }

  if (data == 50)   //DOWN
  {
    digitalWrite(led1, HIGH);
    Serial.println("DOWN");
  }

  if (data == 51)   //LEFT
  {
    digitalWrite(led1, HIGH);
    Serial.println("LEFT");
  }

  if (data == 52)   //RIGHT
  {
    digitalWrite(led1, HIGH);
    Serial.println("RIGHT");
  }

  if (data == 53)   //STOP
  {
    digitalWrite(led1, LOW);
    Serial.println("STOP");
  }

  if (data == 54)   //FORWARD
  {
    digitalWrite(led1, LOW);
    Serial.println("FORWARD");
  }

  if (data == 55)   //BACKWARD
  {
    digitalWrite(led1, LOW);
    Serial.println("BACKWARD");
  }
}
