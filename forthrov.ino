#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
 
ros::NodeHandle nh;
/* 
float var;
float var2;
*/
int depth_setpoint;
float kp,kd,ki;
long randNumber;

float distance;
float distance2; 
int depth;
int front;
/*
void messageCb(const std_msgs::Int32 &msg)
{
  var=msg.data;
}

void messageCb2(const std_msgs::Int32 &msg2)
{
  var2=msg2.data;
}
*/
void message1(const std_msgs::Int32 &msg1)
{
  depth_setpoint=msg1.data;
}

void message2(const std_msgs::Float32 &msg2)
{
  kp=msg2.data;
}

void message3(const std_msgs::Float32 &msg3)
{
  kd=msg3.data;
}

void message4(const std_msgs::Float32 &msg4)
{
  ki=msg4.data;
}
/*
ros::Subscriber<std_msgs::Int32> sub("rand_no", &messageCb);
ros::Subscriber<std_msgs::Int32> sub2("rand_no2", &messageCb2);
*/
ros::Subscriber<std_msgs::Int32> sub1("Measure_depth", &message1);
ros::Subscriber<std_msgs::Float32> sub2("Kp", &message2);
ros::Subscriber<std_msgs::Float32> sub3("Kd", &message3);
ros::Subscriber<std_msgs::Float32> sub4("Ki", &message4);

sensor_msgs::Range sonar_msg; 
ros::Publisher pub("/send_sonar", &sonar_msg); 

ros::Publisher pub2("/send_sonar2", &sonar_msg);

std_msgs::Int32 depth_msg;
ros::Publisher pub_depth("Depth", &depth_msg);

std_msgs::Int32 front_msg;
ros::Publisher pub_front("Front", &front_msg);


char frameid[] ="/sonar_ranger";
unsigned long publisher_timer;

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  /*
  nh.subscribe(sub);
  nh.subscribe(sub2);*/
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.advertise(pub);
  nh.advertise(pub2);
    sonar_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
    sonar_msg.header.frame_id =  frameid;
    sonar_msg.field_of_view = (10.0/180.0) * 3.14;
     sonar_msg.min_range = 0.0;
    sonar_msg.max_range = 10.0;
  
  nh.advertise(pub_depth);
  nh.advertise(pub_front);
    
}
 
void loop()
{/*
  if(var<2500 && var2<2500)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  */

  if(depth_setpoint>80 && kp>5 &&kd>5 &&ki>5)
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

   depth = random(0,25);
   depth_msg.data = depth;
   pub_depth.publish(&depth_msg);
   
   front = random(10,35);
   front_msg.data = front;
   pub_front.publish(&front_msg);
  
  nh.spinOnce();
  //delay(200);
}
