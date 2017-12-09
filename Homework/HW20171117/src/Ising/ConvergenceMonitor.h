#include <cmath>
#include "Eigen/Dense"
using namespace Eigen;
class ConvergenceMonitor
{
    VectorXd    _buffer;
    int         _size;
    int         _pos;
    bool        _full;
public:
    ConvergenceMonitor(const int&);
    void add(const double&);
    double standard_error();
};