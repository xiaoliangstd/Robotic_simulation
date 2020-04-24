#include <iostream>
#include "ros/ros.h"
#include "armcontrol/control.h"
#include "std_msgs/Int8.h"
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
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
double X;
double z;
double y;
double target_x = 0.1;
double target_y = 0.1;
int press;

class Joy_mess
{
  public:
  	Joy_mess();

  private:
  	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

    ros::NodeHandle nh_;

    int linear_, angular_;
    double l_scale_, a_scale_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;

};



Joy_mess::Joy_mess():
  linear_(1),
  angular_(2)  // 初始化变量
{

  nh_.param("axis_linear", linear_, linear_);  // 可以不用加载参数
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);



// 接收手柄信息
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &Joy_mess::joyCallback, this);

}

void Joy_mess::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  
 
  //X = a_scale_*joy->axes[angular_]*0.01;
  z = l_scale_*joy->axes[linear_];
  X = joy->axes[4]*0.01;
  y = joy->axes[3]*0.01;
  press = joy->buttons[0];
  target_x+=X;
  target_y+=y;
  if(target_x == 0)target_x = 0.1;
  if(target_y == 0)target_y = 0.1;
 //std::cout<< target_x<<std::endl;
 std::cout<< press<<std::endl;
}



int main(int argc, char *argv[])
{
	ros::init(argc, argv, "joint_pos_pub");
	Joy_mess jj;
	ros::NodeHandle n;
	Robot robot(n);
	ros::Rate loop_late(1000); 
	//double x,y,z; 
	
	while(1)
	{
		//robot.cal_trajectory(0.1+target_x*0.5,0.1+target_y,0.1+z*0.5,0.1);
		robot.cal_trajectory(0.5,0.2,0.1799,2);
		robot.cal_trajectory(0.5,0.3,0.4,2);
		robot.cal_trajectory(0.0,0.2,0.3,2);
		//ros::spinOnce(); 
		//loop_late.sleep();

	}
	return 0;
}