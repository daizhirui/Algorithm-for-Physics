#include "ConvergenceMonitor.h"
ConvergenceMonitor::ConvergenceMonitor(const int &size)
{
    _size = size;
    _buffer.resize(_size);
    _pos = 0;
    _full = false;
}

void ConvergenceMonitor::add(const double &v)
{
    _buffer(_pos) = v;
    _pos++;
    if(_pos == _size)
        _full = true;
    _pos %= _size;
}

double ConvergenceMonitor::standard_error()
{
        double mean, square_mean;
    if(_full)
    {
        mean = _buffer.mean();
        square_mean = _buffer.squaredNorm() / _size;
    }
    else
    {
        mean = _buffer.head(_pos).mean();
        square_mean = _buffer.head(_pos).squaredNorm() / _pos;
    }
    double std_error = std::sqrt(square_mean - mean * mean);
    return std_error;
}