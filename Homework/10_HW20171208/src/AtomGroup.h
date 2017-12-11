
#ifndef ATOMGROUP_H
#define ATOMGROUP_H
#include "Interaction.h"

using std::string;
class Interaction;
struct Atom
{
    string      atomName;
    string      groupName;
    uint64_t    atomNum;
    uint64_t    groupNum;
    MyVector    position;
    char        atomType;
};

class AtomGroup
{
public:
    uint64_t            groupNum;
    string              groupName;
    MyVector            position;   // the position of CA atom
    double              totalMass;
    vector<Atom>        atomList;
    vector<Interaction> interList;
    AtomGroup();
    AtomGroup(const Atom&);
    void addAtom(const Atom&);
    static double AtomMass(const Atom&);
    void addInteraction(const AtomGroup&);
};

#endif
