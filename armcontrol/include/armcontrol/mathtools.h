#ifndef __MATHTOOLS_H
#define __MATHTOOLS_H

#include <iostream>
#include <math.h>
#include <vector>

#include "eigen3/Eigen/Dense"
#define pi 3.1415926535

class Matrix
{
    public:
        double xx;
        double yy;
        double zz;
        double end_nx;
        double end_ny;
        double end_theta;
        Matrix(std::string ss="Dx",double x=5.0)  // 任意生成
        {
            this->x=x;
            create(ss);
        }

        Matrix get();
        void printf_matrix();   // print suanzi
        void read_matrix();
        void create(std::string ss);
        double read_end();
        Matrix operator* (const Matrix& b)
        {
            Matrix ret;  // 随意生成
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

    private:
        double m[4][4];
        double x;
        void dx();
        void dz();
        void rx();
        void ry();
        void rz();
        

};




#endif