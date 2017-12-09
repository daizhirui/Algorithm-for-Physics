#include <iostream>
#include <ctime>
#include <cstdlib>
#include "RandomWalk.h"
bool RandomWalk::_srand = false;
RandomWalk::RandomWalk()
{
    _possibility = 0.8;
    _steplen = 1.0;
    _position.set_dimension(2);
    init_position();
    if(_srand == false)
    {
        srand((unsigned long)time(nullptr));
        _srand = true;
    }
}

RandomWalk::RandomWalk(const double &p, const double &l, const int &d)
{
    _possibility = p;
    _steplen = l;
    _position.set_dimension(d);
    init_position();
    if(_srand == false)
    {
        srand((unsigned long)time(0));
        _srand = true;
    }
}

void RandomWalk::init_position()
{
    for(int i = 0; i < _position.dimension(); i++)
        _position[i] = 0;
}

void RandomWalk::move()
{
    double poss = rand() % 10000;
    poss /= 10000.0;
    if(poss < _possibility)
    {
        MyVector step(_position.dimension());
        step.random_vector();
        step *= _steplen;
        _position += step;
    }
}

MyVector RandomWalk::position()
{
    return this->_position;
}

double RandomWalk::distance()
{
    return this->_position.modulus();
}