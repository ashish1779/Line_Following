#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float32
from dynamic_reconfigure.server import Server
from firstrov.cfg import TutorialsConfig

def callback(config, level):
    #rospy.loginfo("""{Depth_SetPoint},{Kp},{Kd},{Ki}""".format(**config))
    Depth_SP = """{Depth_SetPoint}""".format(**config)
    KP = """{Kp}""".format(**config)
    KD = """{Kd}""".format(**config)
    KI = """{Ki}""".format(**config)
    int_dep = int(Depth_SP) 
    flo_kp = float(KP)
    flo_kd = float(KD)
    flo_ki = float(KI)
    pub_depth.publish(int_dep)
    pub_kp.publish(flo_kp)
    pub_kd.publish(flo_kd)
    pub_ki.publish(flo_ki)
    print("Depth,Kp,Kd,Ki Published")
    return config

if __name__ == "__main__":
    rospy.init_node("server", anonymous = False)
    pub_depth=rospy.Publisher('Measure_depth', Int32, queue_size=10)
    pub_kp=rospy.Publisher('Kp', Float32, queue_size=10)
    pub_kd=rospy.Publisher('Kd', Float32, queue_size=10)
    pub_ki=rospy.Publisher('Ki', Float32, queue_size=10)
    #rate= rospy.Rate(5)
    srv = Server(TutorialsConfig, callback)
    rospy.spin()
