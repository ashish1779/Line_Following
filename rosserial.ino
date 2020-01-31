/*
  This code is written by ASHISH ANAND.
  Ref: https://www.intorobotics.com/template-for-a-ros-publisher-using-rosserial-on-arduino/
*/

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Int32.h>
 
ros::NodeHandle nh;
 
float var;
float var2;

long randNumber;
float distance;
float distance2; 

void messageCb(const std_msgs::Int32 &msg)
{
  var=msg.data;
}

void messageCb2(const std_msgs::Int32 &msg2)
{
  var2=msg2.data;
}

ros::Subscriber<std_msgs::Int32> sub("rand_no", &messageCb);
ros::Subscriber<std_msgs::Int32> sub2("rand_no2", &messageCb2);

sensor_msgs::Range sonar_msg; 
ros::Publisher pub("/send_sonar", &sonar_msg); 

ros::Publisher pub2("/send_sonar2", &sonar_msg);

char frameid[] ="/sonar_ranger";
unsigned long publisher_timer;

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub2);
  
  nh.advertise(pub);
  nh.advertise(pub2);
    
  sonar_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  sonar_msg.header.frame_id =  frameid;
  sonar_msg.field_of_view = (10.0/180.0) * 3.14;
  sonar_msg.min_range = 0.0;
  sonar_msg.max_range = 10.0;
}
 
void loop()
{
  if(var<2500 && var2<2500)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  
  if ((millis() - publisher_timer)> 50 ) 
   {
   distance = random(0, 10);
   distance2 = random(0, 10);
   //sensoReading = getDistance;
   sonar_msg.range = distance;
   sonar_msg.range = distance2;
   //Serial.println(sensoReading);
   sonar_msg.header.stamp = nh.now();
   pub.publish(&sonar_msg);
   pub2.publish(&sonar_msg);
   publisher_timer = millis(); //publish once a second
   }
  nh.spinOnce();
  //delay(200);
}
