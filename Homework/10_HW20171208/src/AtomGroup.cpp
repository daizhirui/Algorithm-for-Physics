#include <iostream>
#include "AtomGroup.h"
#ifdef __linux__
#include <stdlib.h>
#endif
AtomGroup::AtomGroup(){}
AtomGroup::AtomGroup(const Atom &CAatom)
{
    if (CAatom.atomName != "CA")
    {
        std::cerr << "CAatom's name should be \"CA\"!" << std::endl;
        exit(-1);
    }
    else
    {
        this->groupNum = CAatom.groupNum;
        this->groupName = CAatom.groupName;
        this->position = CAatom.position;
        totalMass = 0.0;
    }
}

void AtomGroup::addAtom(const Atom &v)
{
    atomList.push_back(v);
    totalMass += AtomMass(v);
}

double AtomGroup::AtomMass(const Atom &v)
{
    switch (v.atomType)
    {
    case 'C':
        return 12.0;
    case 'N':
        return 14.0;
    case 'O':
        return 16.0;
    case 'S':
        return 32.0;
    default:
        std::cerr << "No corresponding mass!" << std::endl;
        exit(-1);
    }
}

void AtomGroup::addInteraction(const AtomGroup &v)
{
    if (v.groupNum == this->groupNum + 1)
        interList.push_back(HAR(*this, v)); // add HAR interaction
    if (v.groupNum > this->groupNum + 1)
        if(LJ::isLJ(*this, v))
            interList.push_back(LJ(*this, v)); // add LJ interaction
        else
            interList.push_back(REP(*this, v)); // add REP interaction
    else
        interList.push_back(REP(*this, v)); // add REP interaction
}