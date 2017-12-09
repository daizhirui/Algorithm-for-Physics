#include "MyVector/MyVector.h"
#ifndef PARTICLE_H
#define PARTICLE_H
using namespace std;
class Particle
{
public:
    double      mass;
    MyVector    acceleration;   // a(t)
    MyVector    velocity;       // v(t-1/2*dt) or v(t+1/2*dt)
    MyVector    position;       // r(t) or r(t+dt)
    Particle(const double&, const int&);
    Particle(double&, MyVector&, MyVector&, MyVector&);
    void go(MyVector&, double&);
};

#endif