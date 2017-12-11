//
//  testMyVector.cpp
//
//  Created by 戴植锐 on 2017/11/03.
//  Copyright © 2017年 戴植锐. All rights reserved.
//
#include <iostream>
#include <vector>
#include "MyVector.h"
using namespace std;
void printInfo(const char* str)
{
    cout << str << endl;
}
void printInfo(const char* str, const double& v)
{
    cout << str << v << endl;
}
void printInfo(const char* str, const MyVector& v)
{
    cout << str << v << endl;
}
int main()
{   
    // Test Construct Functions
    printInfo("###### Test Construct Functions ######");
    printInfo("operator<< is also tested when MyVector instance is printed");
    printInfo("void MyVector::set_dimension(int) is also tested");
    printInfo("Test MyVector::MyVector() and int MyVector::dimension()");
    MyVector vector1 = MyVector();
    printInfo("_nDim= ",vector1.dimension());
    printInfo("vector1= ",vector1);

    printInfo("Test MyVector::MyVector(int)");
    MyVector vector2(1);
    printInfo("_nDim= ",vector2.dimension());
    printInfo("vector2= ",vector2);

    printInfo("Test MyVector::MyVector(int,vector)");
    double num[] = {1,0,1,0};
    vector<double> vector0(num,num+4);
    MyVector vector3(4,vector0);
    printInfo("_nDim= ",vector3.dimension());
    printInfo("vector3= ",vector3);

    printInfo("Test MyVector::MyVector(int,double)");
    double pos[]={1,2,3,4,5};
    MyVector vector4(sizeof(pos)/sizeof(double),pos);
    printInfo("_nDim= ",vector4.dimension());
    printInfo("vector4= ",vector4);

    printInfo("Test MyVector::MyVector(MyVector)\n and operator= (inside this Construct Function)");
    MyVector vector5(vector4);
    printInfo("_nDim= ",vector5.dimension());
    printInfo("vector5= ",vector5);
    printInfo("");

    // Test Member value set-function and get-function
    printInfo("Test void MyVector::set_position");
    printInfo("Before set_position(vector0), vector1._nDim= ",vector1.dimension());
    printInfo("Before set_position(vector0), vector1= ",vector1);
    vector1.set_position(vector0);
    printInfo("After set_position(vector0), vector1._nDim= ",vector1.dimension());
    printInfo("After set_position(vector0), vector1= ",vector1);
    printInfo("");

    // Test operators
    printInfo("###### Test operators ######");
    printInfo("Test double& MyVector::operator[](int) or double MyVector::operator[](int) const");
    cout << "vector1[0]= " << vector1[0] << endl;
    vector1.set_dimension(3);
    vector0.resize(3);
    for(int i=0;i<3;i++)
        vector0[i] = i;
    vector1.set_position(vector0);  // vector1 = (0, 1, 2)
    vector2.set_dimension(3);
    for(int i=1;i<4;i++)
        vector0[i-1] = i;
    vector2.set_position(vector0);  // vector2 = (1, 2, 3)
    printInfo("Test operator+ - * /");
    printInfo("\t vector1 = ",vector1);
    printInfo("\t vector2 = ",vector2);
    printInfo("vector1 + vector2 = ",vector1 + vector2);
    printInfo("vector1 - vector2 = ",vector1 - vector2);
    printInfo("vector1 * 3 = ", vector1 * 3);
    printInfo("3 * vector1 = ", 3 * vector1);
    printInfo("vector1 / 3 = ", vector1 / 3);
    printInfo("-vector1 = ", -vector1);
    vector1 += vector2;
    printInfo("vector1 += vector2, vector1 = ", vector1);
    vector1 -= vector2;
    printInfo("vector1 -= vector2, vector1 = ", vector1);
    vector1 *= 5;
    printInfo("vector1 *= 5, vector1 = ", vector1);
    vector1 /= 5;
    printInfo("vector1 /= 5, vector1 = ", vector1);
    if(vector1 == vector2)
        printInfo("vector1 == vector 2: true");
    else
        printInfo("vector1 == vector 2: false");
    if(vector1 == vector1)
        printInfo("vector1 == vector 1: true");
    else
        printInfo("vector1 == vector 1: false");
    if(vector1 != vector2)
        printInfo("vector1 == vector 2: true");
    else
        printInfo("vector1 == vector 2: false");
    if(vector1 != vector1)
        printInfo("vector1 == vector 1: true");
    else
        printInfo("vector1 == vector 1: false");
    printInfo("");
    // Test normalize(d) modulus and set_modulus
    vector0[0] = 1;
    vector0[1] = 1;
    vector0[2] = 0;
    vector1.set_position(vector0);
    printInfo("###### Test normalize(d) modulus and set_modulus ######");
    printInfo("Before vector1.normalize(), vector1 = ", vector1);
    printInfo("vector1.normalize() = ", vector1.normalize());
    printInfo("After vector1.normalize(), vector1 = ", vector1);
    printInfo("Before vector1.normalized(), vector1 = ", vector1);
    vector1.normalized();
    printInfo("vector1.normalized() = ", vector1);
    printInfo("After vector1.normalized(), vector1 = ", vector1);
    printInfo("vector1.modulus() = ",vector1.modulus());
    vector1.set_modulus(2);
    printInfo("After vector1.set_modulus(2), vector1 = ",vector1);
    printInfo("vector1.modulus() = ",vector1.modulus());
    printInfo("");

    //Test dot cross
    printInfo("###### Test dot and cross ######");
    vector1.set_position(vector0);
    printInfo("\t vector1 = ",vector1);
    printInfo("\t vector2 = ",vector2);
    printInfo("vector1.dot(vector2) = ",vector1.dot(vector2));
    printInfo("vector2.dot(vector1) = ",vector2.dot(vector1));
    printInfo("vector1.dot(vector1) = ",vector1.dot(vector1));
    printInfo("dot(vector1, vector2) = ", MyVector::dot(vector1, vector2));
    printInfo("dot(vector2, vector1) = ", MyVector::dot(vector2, vector1));
    printInfo("dot(vector1, vector1) = ", MyVector::dot(vector1, vector1));
    printInfo("vector1.cross(vector2) = ",vector1.cross(vector2));
    printInfo("vector2.cross(vector1) = ",vector2.cross(vector1));
    printInfo("vector1.cross(vector1) = ",vector1.cross(vector1));
    printInfo("cross(vector1, vector2) = ", MyVector::cross(vector1, vector2));
    printInfo("cross(vector2, vector1) = ", MyVector::cross(vector2, vector1));
    printInfo("cross(vector1, vector1) = ", MyVector::cross(vector1, vector1));
    printInfo("");

    //Test angleBetween dist
    printInfo("###### Test angleBetween and dist ######");
    printInfo("\t vector1 = ",vector1);
    printInfo("\t vector2 = ",vector2);
    vector3 = vector1.cross(vector2);
    printInfo("\t vector3 = vector1 x vector2 ",vector3);
    printInfo("vector1.angleBetween(vector3) = ", vector1.angleBetween(vector3));
    printInfo("vector3.angleBetween(vector1) = ", vector3.angleBetween(vector1));
    printInfo("angleBetween(vector1, vector3) = ", MyVector::angleBetween(vector1, vector3));
    printInfo("angleBetween(vector3, vector1) = ", MyVector::angleBetween(vector3, vector1));
    printInfo("\t vector1 = ",vector1);
    printInfo("\t vector2 = ",vector2);
    printInfo("\t vector3 = vector1 x vector2 ",vector3);
    printInfo("vector1.dist(vector2) = ", vector1.dist(vector2));
    printInfo("vector2.dist(vector1) = ", vector2.dist(vector1));
    printInfo("dist(vector1, vector2) = ", MyVector::dist(vector1, vector2));
    printInfo("dist(vector2, vector1) = ", MyVector::dist(vector2, vector1));
    printInfo("");

    //Test random_vector
    printInfo("###### Test random_vector ######");
    printInfo("Before vector1.random_vector(), vector1 = ", vector1);
    vector1.random_vector();
    printInfo("vector1.random_vector() = ", vector1);
    printInfo("After vector1.random_vector(), vector1 = ", vector1);
    printInfo("Now we generate a new vector randomly and give it to vector5");
    printInfo("Before that, vector5 = ", vector5);
    vector5 = MyVector::random_vector(4);
    printInfo("vector5 = MyVector::random_vector(4) = ", vector5);
    printInfo("vector5.modulus() = ", vector5.modulus());
    printInfo("");
    
    printInfo("******** Congratulations! Test Completed! ********");
    return 0;
}