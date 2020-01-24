#ifndef CONTROL_H
#define CONTROL_H

#include "ros/ros.h"
#include "armcontrol/mathtools.h"
#include "sensor_msgs/JointState.h"
#include <math.h>


#define L1 0.6
#define L2 0.64

class Robot
{

    public:
        friend class subandpub;
        Robot(ros::NodeHandle& n)
        {
            position_pub = n.advertise<sensor_msgs::JointState>("/joint_states", 3000);
        };
        void fk(double angle1,double angle2,double angle3);
        void ik(double x,double y,double z);
        void cal_trajectory(double x,double y,double z,double tf);
        void pub(double angle1,double angle2,double angle3);
        double end_theta;
    private:

    ros::Publisher position_pub;
    sensor_msgs::JointState joint_state;
    double angle11,angle22,angle33;
	double angle1 = 0;
	double angle2 = 0;
	double angle3 = 0;
    double last_theta1 = 0,last_theta2 = 0,last_theta3 = 0;
    double theta1,theta2,theta3;
    
		
};




#endif