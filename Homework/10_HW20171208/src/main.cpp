#include <iostream>
#include <fstream>
#include <map>
#include "AtomGroup.h"
#include "pdbAnalyser.h"
#include "terminal_IO.h"
int main(int argc, char* argv[])
{
    ParamBox v;
    v.in_filename = "1COA.pdb";
    v.out_filename = "result.txt";
    process_param(argc, argv, v);

    ifstream ifs;
    ifs.open(v.in_filename, ios::in);
    if(!ifs.is_open())
    {
        cout << "Fail to create the file stream!" << endl;
        exit(-1);
    }
    map<int, AtomGroup> atomGroupList;
    vector<Atom> temp_atomList;
    Atom temp_atom;
    string temp;
    while (getline(ifs, temp))
    {
        if(pdbAnalyser(temp_atom, temp))
        {
            temp_atomList.push_back(temp_atom);
            if(temp_atom.atomName == "CA")
                atomGroupList[temp_atom.groupNum] = AtomGroup(temp_atom);
        }
    }
    ifs.close();

    for(auto n:temp_atomList)
    {
        atomGroupList[n.groupNum].addAtom(n);
    }

    for(auto &n:atomGroupList)
        for(auto &m:atomGroupList)
            if(n.first != m.first)
                n.second.addInteraction(m.second);

    ofstream ofs;
    ofs.open(v.out_filename, ios::out);
    if(!ofs.is_open())
    {
        cerr << "Fail to create file " << v.out_filename << " !" << endl;
        exit(-1);
    }
    else
        ofs << "ATOM PART" << endl
            << "-----------------------------------" << endl
            << "ATOMGROUP_NAME\t" << "ATOMGROUP_NUM\t" << "ATOMGROUP_MASS\t" << "ATOMGROUP_POS" << endl;

    for(auto n:atomGroupList)
        ofs << n.second.groupName << '\t' << n.first << '\t' << n.second.totalMass << '\t' << n.second.position << endl;

    ofs << endl << "INTERACTION PART" << endl
                << "-------------------------------" << endl
                << "TYPE\tGROUP1\tGROUP2\tMAGNITUDE\tDISTANCE" << endl;
    for(auto j:atomGroupList)
        for(auto n:j.second.interList)
        ofs << n.interName << '\t' << n.member1 << '\t' << n.member2 << '\t' << n.magnitude << '\t' << n.distance << endl;

    ofs.close();

    cout << "Data Analyse Completed!" << endl
         << "The result is stored in " << v.out_filename << endl;
    return 0;
}