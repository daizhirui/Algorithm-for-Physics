#include <iostream>
#include <fstream>
#include "RandomWalk.h"
int main()
{
    srand((unsigned long)time(nullptr));
    RandomWalk rw(0.8, 1.0, 2);
    MyVector pos;
    ofstream ofs;
    ofs.open("track.txt", ios::out);
    for(int i = 0; i < 1000; i++)
    {
        rw.move();
        pos = rw.position();
        ofs << i << '\t' << pos[0] << '\t' << pos[1] << '\t' << rw.distance() << endl;
    }
    ofs.close();
}