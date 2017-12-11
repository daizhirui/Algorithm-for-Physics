#include <cmath>
#include "Interaction.h"

Interaction::Interaction(const AtomGroup &group1, const AtomGroup &group2, const double &mag)
{
    interName = "INTERACTION";
    member1 = group1.groupNum;
    member2 = group2.groupNum;
    magnitude = mag;
    distance = group1.position.dist(group2.position);
}

HAR::HAR(const AtomGroup &group1, const AtomGroup &group2) : Interaction(group1, group2, 100.0)
{
    interName = "HAR";
}

LJ::LJ(const AtomGroup &group1, const AtomGroup &group2) : Interaction(group1, group2, 100.0)
{
    int count = 0;
    for (auto n : group1.atomList)
    {
        for (uint i = 0; i < group2.atomList.size(); i++)
            if (n.position.dist(group2.atomList[i].position) < 5.0)
                count++;
    }
    magnitude = std::log((double)count); // reset magnitude
    distance = group1.position.dist(group2.position); // reset distance
    interName = "LJ";
}

bool LJ::isLJ(const AtomGroup &group1, const AtomGroup &group2)
{
    bool is = false;
    for (auto n : group1.atomList)
    {
        for (uint i = 0; i < group2.atomList.size(); i++)
            if (n.position.dist(group2.atomList[i].position) < 5.0)
            {
                is = true;
                break;
            }
        if (is)
            break;
    }
    return is;
}

REP::REP(const AtomGroup &group1, const AtomGroup &group2) : Interaction(group1, group2, 1.0)
{
    distance = 4.0;
    interName = "REP";
}