//
//  MyVector.h
//
//  Created by 戴植锐 on 2017/11/03.
//  Copyright © 2017年 戴植锐. All rights reserved.
//
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <vector>
using namespace std;

class MyVector
{
    int  _nDim;
    vector<double> _data;
public:
    MyVector();
    MyVector(int);
    MyVector(int, const vector<double>&);
    MyVector(int, const double*);
    MyVector(const MyVector&);
    ~MyVector();

    void set_dimension(int);
    int dimension();

    void set_position(const vector<double>&);
    void set_position(const double*);

    double& operator[](int);
    double operator[](int) const;

    void operator=(const MyVector&);
    MyVector operator+(const MyVector&) const;
    MyVector operator-(const MyVector&) const;
    MyVector operator-() const;
    MyVector operator*(const double&) const;
    friend MyVector operator*(const double&, const MyVector&);
    MyVector operator/(const double&);

    MyVector operator+=(const MyVector&);
    MyVector operator-=(const MyVector&);
    MyVector operator*=(const double&);
    MyVector operator/=(const double&);
    friend ostream& operator<<(ostream&, const MyVector&);
    bool operator==(const MyVector&) const;
    bool operator!=(const MyVector&) const;

    MyVector normalize() const;
    void normalized();
    double modulus() const;
    void set_modulus(const double&);

    double dot(const MyVector&) const;
    static double dot(const MyVector&, const MyVector&);
    MyVector cross(const MyVector&) const;
    static MyVector cross(const MyVector&, const MyVector&);
    double angleBetween(const MyVector&) const;
    static double angleBetween(const MyVector&, const MyVector&);
    double dist(const MyVector&) const;
    static double dist(const MyVector&, const MyVector&);
    //MyVector rotate2D(const MyVector&, const double&) const;
    //void rotate2D();
    //MyVector rotate3D() const;
    //void rotated3D();

    void random_vector();
    static MyVector random_vector(int);
};

#endif