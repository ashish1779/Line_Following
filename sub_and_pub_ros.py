#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32
from random import randint
 
#a function to generate the random number
def generate_random_number():
    rnd= randint(0,5000)
    #rnd = int(input())
    return rnd

def generate_random_number2():
    rnd= randint(0,5000)
    #rnd = int(input())
    return rnd

if __name__=='__main__':
    rospy.init_node('random_number')
    pub=rospy.Publisher('rand_no', Int32, queue_size=10)
    pub2=rospy.Publisher('rand_no2', Int32, queue_size=10)
    rate= rospy.Rate(5)
 
    while not rospy.is_shutdown():
	#rnd_gen=button1()        
	rnd_gen=generate_random_number()
        rnd_gen2=generate_random_number2()
        rospy.loginfo("You entered: %s", rnd_gen)
	rospy.loginfo("You entered2: %s", rnd_gen2)
        pub.publish(rnd_gen)
        pub2.publish(rnd_gen2)

rate.sleep()
