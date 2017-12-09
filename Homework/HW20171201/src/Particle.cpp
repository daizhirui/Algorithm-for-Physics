#include <iostream>
#include "Particle.h"

Particle::Particle(const double &m, const int &v)
{
    mass = m;
    acceleration.set_dimension(v);
    velocity.set_dimension(v);
    position.set_dimension(v);
}

Particle::Particle(double &m, MyVector &v, MyVector &a, MyVector &r)
{
    if(v.dimension() == a.dimension() && v.dimension() == r.dimension())
    {
        mass = m;
        velocity = v;
        acceleration = a;
        position = r;
    }
    else
    {
        cout << "Position, acceleration and velocity's dimensions are different!" << endl;
        exit(-1);
    }
}

void Particle::go(MyVector &f, double &dt)
{
    acceleration = f / mass;
    velocity = velocity + acceleration * dt;
    position = position + velocity * dt;
}