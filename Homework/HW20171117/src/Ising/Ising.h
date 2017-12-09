#include <iostream>

#include "Eigen/Dense"
#include "terminal_IO.h"
using namespace std;
using namespace Eigen;
typedef Matrix<double, 5, 1> Vector5d;
class Ising
{
    int         _size;
    MatrixXd    _lattice;
    double      _temperature;
    double      _mutualCoefficient;
    double      _totalEnergy;
    double      _totalMagnism;
    void init_lattice();
    Vector5d get_nearby(int&, int&);
    void init_Energy();
    void init_Magnetism();
    double delta_Energy(int&, int&);
public:
    Ising(ParamBox&);
    double total_Energy();
    double total_Magnetism();
    bool flip();
};