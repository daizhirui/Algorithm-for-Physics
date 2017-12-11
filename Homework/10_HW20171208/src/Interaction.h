#include <cstdint>
#include <iostream>
#include <string>
#include <cstdint>
#include "MyVector/MyVector.h"
#include "AtomGroup.h"
#ifndef INTERACTION_H
#define INTERACTION_H
using std::ostream;
class AtomGroup;
class Interaction
{
public:
    string      interName;
    uint64_t    member1;
    uint64_t    member2;
    double      magnitude;
    double      distance;
    Interaction(const AtomGroup&, const AtomGroup&, const double&);
    friend ostream& operator<<(ostream&, const Interaction&);
};

class HAR: public Interaction
{
public:
    HAR(const AtomGroup&, const AtomGroup&);
};

class LJ: public Interaction
{
public:
    LJ(const AtomGroup&, const AtomGroup&);
    static bool isLJ(const AtomGroup&, const AtomGroup&);
};

class REP: public Interaction
{
public:
    REP(const AtomGroup&, const AtomGroup&);
};
#endif