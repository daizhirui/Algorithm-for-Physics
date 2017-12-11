#include <ctime>
#include <cstdlib>
#include <cmath>

#include "Ising.h"
#include "Config.h"

Ising::Ising(ParamBox& v)
{
    _size = v.size;                             // store the size
    _lattice.resize(_size, _size);              // setup the size of the lattice
    _temperature = v.temperature;               // setup the temperature of the lattice
    _mutualCoefficient = v.mutual_coeff;        // setup the mutual effect coefficient
    init_lattice();                             // Randomly initialize the lattice
    init_Energy();
    init_Magnetism();
}

void Ising::init_lattice()
{
    srand((unsigned long)time(0));          // random seed initilization
    for(int row = 0; row < _size; row++)
        for(int col = 0; col < _size; col++)
            _lattice(row, col) = rand()%2;
}

void Ising::init_Energy()
{
    _totalEnergy = 0;
    for(int row = 0; row < _size; row++)
        for(int col = 0; col < _size; col++)
        {
            Vector5d vect = get_nearby(row, col);
            _totalEnergy += -(vect(1) + vect(2) + vect(3) + vect(4))*vect(0)*_mutualCoefficient;
        }
    _totalEnergy /= 2.0;
}

double Ising::total_Energy()
{
    return _totalEnergy;
}

double Ising::delta_Energy(int& row, int& col)
{
    Vector5d vect = get_nearby(row, col);
    return -2*_mutualCoefficient*vect(0)*(vect(1) + vect(2) + vect(3) + vect(4));
}

void Ising::init_Magnetism()
{
    _totalMagnism = _lattice.sum();
}

double Ising::total_Magnetism()
{
    return _totalMagnism;
}

bool Ising::flip()
{
    int row = rand() % _size;
    int col = rand() % _size;
    double deltaE = delta_Energy(row, col);
    bool toFlip = false;
    if(deltaE < 0)
        toFlip = true;
    else
    {
        double possible = (rand() % 1000) / 1000.0;
        if(possible < expl(-deltaE * _temperature))
            toFlip = true;
    }
    if(toFlip)
    {
        double temp = _lattice(row, col);
        _lattice(row, col) = -temp;         // flip the spin
        _totalEnergy += deltaE;             // update the total energy
        _totalMagnism -= 2 * temp;          // update the total magnetism
        return true;
    }
    else
        return false;
}

Vector5d Ising::get_nearby(int& row, int& col)
{
    Vector5d vect;
    vect(0) = _lattice(row, col);
    vect(1) = _lattice((row - 1 + _size) % _size, col); // up
    vect(2) = _lattice((row + 1 + _size) % _size, col); // down
    vect(3) = _lattice(row, (col - 1 + _size) % _size); // left
    vect(4) = _lattice(row, (col + 1 + _size) % _size); // right
    return vect;
}

