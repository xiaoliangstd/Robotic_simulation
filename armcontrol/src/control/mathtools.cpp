#include "armcontrol/mathtools.h"


Matrix Matrix::operator* (const Matrix& b)
{

    Matrix ret;  
    int i,j,k;  
    double c[4][4];  
    double sum = 0;   
    for(i = 0;i<4;i++)
    {
        for(j = 0;j<4;j++)
        { 
            for(k = 0;k<4;k++) {sum+=this->m[i][k]*b.m[k][j];}
            ret.m[i][j] = sum;
            sum = 0;
        }
    }
    return ret;
}



void Matrix::read_matrix()
{
    
    std::cout<<"x:"<< this->m[0][3]<<std::endl;
    std::cout<<"y:"<< this->m[1][3]<<std::endl;
    std::cout<<"z:"<< this->m[2][3]<<std::endl;


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



Dx::Dx(double x)
{
    this->x = x;
    this->create();

}

void Dx::create()
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



Rx::Rx(double x)
{
    this->x = x;
    this->create();

}

void Rx::create()
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



Ry::Ry(double x)
{
    this->x = x;
    this->create();

}

void Ry::create()
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


Rz::Rz(double x)
{
    this->x = x;
    this->create();
}

void Rz::create()
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



Dz::Dz(double x)
{
    this->x = x;
    this->create();
}

void Dz::create()
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




