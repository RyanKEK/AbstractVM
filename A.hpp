#ifndef A_HPP
#define A_HPP

#include "B.hpp"

class B;

class A
{
private:
    
    //B b;

public:
    A(B b);
    ~A();
};

A::A(B b)
{
}

A::~A()
{
}


#endif
