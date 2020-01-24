#include "armcontrol/mathtools.h"


 

void Matrix::dx()
{
    int i,j;
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {   
                if(i==j){this->m[i][j]=1;continue;}
                if(i==0&&j==3){this->m[i][j]=this->x;continue;}
                this->m[i][j] = 0;
            }
        }
}

void Matrix::dz()
{
     int i,j;
        static double d[4][4];
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {   
                if(i==j){this->m[i][j]=1;continue;}
                if(i==2&&j==3){this->m[i][j]=this->x;continue;}
                this->m[i][j] = 0;
            }
        }
}

void Matrix::rx()
{

    int i,j;
    double xx;
    xx = this->x*(pi/180);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {   
            if(i==0&&j==0){this->m[i][j]=1;continue;}
            if(i==1&&j==1){this->m[i][j]=cos(xx);continue;}
            if(i==2&&j==1){this->m[i][j]=sin(xx);continue;}
            if(i==1&&j==2){this->m[i][j]=-sin(xx);continue;}
            if(i==2&&j==2){this->m[i][j]=cos(xx);continue;}
            if(i==3&&j==3){this->m[i][j]=1;continue;}
    
            this->m[i][j] = 0;
        }
    }

}


void Matrix::ry()
{

    int i,j;
    double xx;
    xx = this->x*(pi/180);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {   
            if(i==0&&j==0){this->m[i][j]=1;continue;}
            if(i==1&&j==1){this->m[i][j]=cos(xx);continue;}
            if(i==2&&j==1){this->m[i][j]=sin(xx);continue;}
            if(i==1&&j==2){this->m[i][j]=-sin(xx);continue;}
            if(i==2&&j==2){this->m[i][j]=cos(xx);continue;}
            if(i==3&&j==3){this->m[i][j]=1;continue;}
    
            this->m[i][j] = 0;
        }
    }

}


void Matrix::rz()
{

    int i,j;
    double xx;
    xx = this->x*(pi/180);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {   
            if(i==0&&j==0){this->m[i][j]=cos(xx);continue;}
            if(i==1&&j==0){this->m[i][j]=sin(xx);continue;}
            if(i==0&&j==1){this->m[i][j]=-sin(xx);continue;}
            if(i==1&&j==1){this->m[i][j]=cos(xx);continue;}
            if(i==2&&j==2){this->m[i][j]=1;continue;}
            if(i==3&&j==3){this->m[i][j]=1;continue;}
    
            this->m[i][j] = 0;
        }
    }

}

void Matrix::create(std::string ss)
{
    if(ss =="Dx") dx();
    if(ss =="Dz") dz();
    if(ss =="Rx") rx();
    if(ss =="Rz") rz();


}

void Matrix::read_matrix()
{
    
    std::cout<<"x:"<< this->m[0][3]<<std::endl;
    std::cout<<"y:"<< this->m[1][3]<<std::endl;
    std::cout<<"z:"<< this->m[2][3]+0.179<<std::endl;
    this ->xx = this->m[0][3];
    this ->yy = this->m[1][3];
    this ->zz = this->m[2][3];

}

double Matrix::read_end()
{
    double theta1;
    //std::cout<<"ay:"<< this->m[1][2]<<std::endl;
    //std::cout<<"az:"<< this->m[2][2]<<std::endl;
    this ->end_nx = this->m[0][0];
    this ->end_ny = this->m[0][1];
    theta1 = atan2(this->end_ny,this->end_nx);
    theta1 = theta1*(180/3.1415926);
    //std::cout<<"theta1:"<< theta1<<std::endl;
    return theta1;
}


void Matrix::printf_matrix()
{
    int i,j;
    std::cout<<"the matrix is:"<<std::endl;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {   
            if(j== 3) 
            {  
                std::cout<< this->m[i][j] <<std::endl;continue;
            }
            if(this->m[i][j] < 0.0001 && this->m[i][j]> -0.0001) {std::cout<< 0 << " " ;continue;}  // 不输出小数点
            std::cout<< this->m[i][j] <<" ";
        }
    }
}

 

