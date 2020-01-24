#include <iostream>
#include "ros/ros.h"
#include "armcontrol/control.h"
#include "std_msgs/Int8.h"

/*  FK    */
/*
		std::cout<<"angle1:";
		std::cin>>angle1;
		std::cout<<"angle2:";
		std::cin>>angle2;
		std::cout<<"angle3:";
		std::cin>>angle3;
		robot.fk(angle1,angle2,angle3);

*/

/*  IK  */
/*
		std::cout<<"X:";
		std::cin>>Z;
		std::cout<<"Y:";
		std::cin>>Z;
		std::cout<<"Z:";
		std::cin>>Z;
		robot.ik(x,y,z);

*/

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "joint_pos_pub");
	ros::NodeHandle n;
	Robot robot(n);
	ros::Rate loop_late(1000); 
	//double x,y,z; 
	while(1)
	{
		
		robot.cal_trajectory(0,0.4,0.4,2);
		robot.cal_trajectory(0.7,0.7,0.7,4);
		robot.cal_trajectory(0,0.5,0.6,4);
		
		

	}


	return 0;
}