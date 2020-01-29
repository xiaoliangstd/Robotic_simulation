#ifndef __MATHTOOLS_H
#define __MATHTOOLS_H

#include <iostream>
#include <math.h>



#define pi 3.1415926535

class Matrix
{
    public:
        Matrix(){};
        void printf_matrix();   // print suanzi
        void read_matrix();
        Matrix operator* (const Matrix& b);
        
    protected:
        double m[4][4];

};

  

class Dx : public Matrix
{
    public:
        Dx(double x);

    private:
        double x;
        void create();

};



class Rx : public Matrix
{
    public:
        Rx(double x);

    private:
        double x;
        void create();


};


class Ry : public Matrix
{
    public:
        Ry(double x);

    private:
        double x;
        void create();


};

class Rz : public Matrix
{
    public:
        Rz(double x);

    private:
        double x;
        void create();
};


class Dz : public Matrix
{
    public:
        Dz(double x);

    private:
        double x;
        void create();

};

#endif