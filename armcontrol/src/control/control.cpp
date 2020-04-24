#include "armcontrol/control.h"


void Robot::fk(double angle1,double angle2,double angle3)
{
    double x,y,z;
    Matrix rz1("Rz",angle1);
    Matrix rx2("Rx",90),rz2("Rz",angle2);
    Matrix dx3("Dx",0.6),rz3("Rz",angle3);
    Matrix dx4("Dx",0.64);
    Matrix frame1,frame2,frame3,frame4,frame_all;
    frame1 = rz1;
    frame2 = rx2*rz2;
    frame3 = dx3*rz3;
    frame4 = dx4;
    frame_all = frame2*frame3*frame4;
    frame_all.printf_matrix();
    this->end_theta = frame_all.read_end();
    //this->pub(angle1,angle2,angle3);
    /*
    x = frame_all.xx;
    y = frame_all.yy;
    z = frame_all.zz;
    this->ik(x,y,z);
    */

}


void Robot::fk1(double angle1,double angle2,double angle3)
{
    Vec44<double> rz1;
    rz1<<1,1,1,1,
         1,1,1,1,
         1,1,1,1,
         0,0,0,1;
   std::cout<<rz1<<std::endl;

}


// 仅仅算出系数矩阵

void Robot::cal_trajectory(double x,double y,double z,double tf)
{
    double c0_1,c1_1,c2_1,c3_1,c0_2,c1_2,c2_2,c3_2,c0_3,c1_3,c2_3,c3_3,t,theta1;
    double theta1_i,theta1_i_speed,theta1_f,theta1_f_speed,theta2_i,theta2_i_speed,theta2_f,theta2_f_speed,theta3_i,theta3_i_speed,theta3_f,theta3_f_speed;
    this->ik(x,y,z);
    ros::Rate loop_rate(1000);
    theta1_i = this->last_theta1;
    theta1_i_speed = 0;
    theta1_f = this->theta1;
    theta1_f_speed = 0;

    theta2_i = this->last_theta2;
    theta2_i_speed = 0;
    theta2_f = this->theta2;
    theta2_f_speed = 0;

    theta3_i = this->last_theta3;
    theta3_i_speed = 0;
    theta3_f = this->theta3;
    theta3_f_speed = 0;
   
    c0_1 = theta1_i;
    c1_1 = theta1_i_speed;
    c2_1 = -(3/pow(tf,2))*theta1_i-(2/tf)*theta1_i_speed+(3/pow(tf,2)*theta1_f-(1/tf)*theta1_f_speed);
    c3_1 = (2/pow(tf,3))*theta1_i+(1/pow(tf,2))*theta1_i_speed-(2/pow(tf,3))*theta1_f+(1/pow(tf,2))*theta1_f_speed;
   
    c0_2 = theta2_i;
    c1_2 = theta2_i_speed;
    c2_2 = -(3/pow(tf,2))*theta2_i-(2/tf)*theta2_i_speed+(3/pow(tf,2)*theta2_f-(1/tf)*theta2_f_speed);
    c3_2 = (2/pow(tf,3))*theta2_i+(1/pow(tf,2))*theta2_i_speed-(2/pow(tf,3))*theta2_f+(1/pow(tf,2))*theta2_f_speed;
   
    c0_3 = theta3_i;
    c1_3 = theta3_i_speed;
    c2_3 = -(3/pow(tf,2))*theta3_i-(2/tf)*theta3_i_speed+(3/pow(tf,2)*theta3_f-(1/tf)*theta3_f_speed);
    c3_3 = (2/pow(tf,3))*theta3_i+(1/pow(tf,2))*theta3_i_speed-(2/pow(tf,3))*theta3_f+(1/pow(tf,2))*theta3_f_speed;

    for(t = 0;t<tf;t+=0.001)
    {
        theta1 = c0_1+c1_1*t+c2_1*pow(t,2)+c3_1*pow(t,3);
        theta2 = c0_2+c1_2*t+c2_2*pow(t,2)+c3_2*pow(t,3);
        theta3 = c0_3+c1_3*t+c2_3*pow(t,2)+c3_3*pow(t,3);
        //std::cout<<theta1<<std::endl;
      
        this->pub(theta1,theta2,theta3);
        double the1 = theta1*(180/pi);   // 粗心阿  一个错误  不会debug 唉
        double the2 = theta2*(180/pi);
        double the3 = theta3*(180/pi);

        this->fk(the1,the2,the3);
        loop_rate.sleep();
    }
    this->last_theta1 = this->theta1;
    this->last_theta2 = this->theta2;
    this->last_theta3 = this->theta3;
}


void Robot::ik(double x,double y,double z)
{
    double theta1,cos_theta3,sin_theta3,theta2,theta3,k1,k2,temp1,temp_1,temp_z,temp2;  
    z = z - 0.1799 ;
    theta1 = atan2(y,x);
    temp1 = x*cos(theta1)+y*sin(theta1);
    temp_1 = pow(temp1,2);
    temp_z = pow(z,2);
    cos_theta3 = (temp_1+temp_z-pow(L1,2)-pow(L2,2))/(2*L1*L2);
    sin_theta3 = -sqrt(1-pow(cos_theta3,2));  // 多解
    theta3 = atan2(sin_theta3,cos_theta3);
    k1 = L1+L2*cos_theta3;
    k2 = L2*sin_theta3;
    temp2 = x*cos(theta1)+y*sin(theta1);
    theta2 = atan2(z,temp2) - atan2(k2,k1);
    
    //this->pub(theta1,theta2,theta3);
    this->theta1 = theta1;
    this->theta2 = theta2;
    this->theta3 = theta3;
    //theta1 = theta1*(180/pi);
   // theta2 = theta2*(180/pi);
   // theta3 = theta3*(180/pi);
   // this->fk1(theta1,theta2,theta3);
    //std::cout<<"theta1:"<<theta1<<std::endl;
    //std::cout<<"theta2:"<<theta2<<std::endl;
    //std::cout<<"theta3:"<<theta3<<std::endl;

}


void Robot::pub(double angle1,double angle2,double angle3)
{
            /*  annotate when use ik functrion
            double angle11,angle22,angle33;
            angle11 = angle1*(pi/180);
	        angle22 = angle2*(pi/180);
	        angle33 = angle3*(pi/180);
            */
            joint_state.header.stamp = ros::Time::now();
		    joint_state.name={"arm_rot_1","arm_rot_2","arm_rot_3","arm_rot_5","arm_rot_6","finger_pri_1"};
            joint_state.position = {angle1,angle2,angle3,this->end_theta,0,0.1};
		    position_pub.publish(joint_state);



}
