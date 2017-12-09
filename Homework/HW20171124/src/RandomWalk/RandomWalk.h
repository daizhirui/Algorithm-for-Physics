#include "../MyVector/MyVector.h"
#include <vector>
class RandomWalk
{
    static bool _srand;
    double   _possibility;
    double   _steplen;
    MyVector _position;
    void init_position();
public:
    RandomWalk();
    RandomWalk(const double &p, const double &l, const int &d);// possibility, steplen, dimension
    void move();
    MyVector position();
    double distance();
};