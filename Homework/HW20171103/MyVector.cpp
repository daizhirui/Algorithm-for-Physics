//
//  MyVector.cpp
//
//  Created by 戴植锐 on 2017/11/03.
//  Copyright © 2017年 戴植锐. All rights reserved.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "MyVector.h"
using namespace std;
MyVector::MyVector() : _data(3)
{
    _nDim = 3;                  // initialize the dimension, default 3
}

MyVector::MyVector(int dimension) : _data(3)
{
    set_dimension(dimension);   // initialize the dimension
}

MyVector::MyVector(int dimension, const vector<double>& v): _data(3)
{
    set_dimension(dimension);   // initialize the dimension
    set_position(v);            // update the position
}

MyVector::MyVector(int dimension, const double* v): _data(3)
{
    set_dimension(dimension);   // initialize the dimension
    set_position(v);            // update the position
}

MyVector::MyVector(const MyVector& v): _data(3)
{
    *this = v;
}

MyVector::~MyVector()
{
    _nDim = 0;
    _data.resize(0);
}

void MyVector::set_dimension(int dimension)
{
    if (dimension > 0)      // check the dimension
    {
        _nDim = dimension;  // update the dimension
        _data.resize(_nDim);// resize the position vector
    }
    else                    // dimension error
    {
        cout << "MyVector::set_dimension(int) Error: dimension <= 0" << endl;
        exit(-1);
    }
}

int MyVector::dimension()
{
    return this->_nDim;
}

void MyVector::set_position(const vector<double>& v)
{
    if(_nDim > (int)v.size())
    {
        cout << "MyVector::set_dimension(vector) Error: vector is shorter than MyVector object" << endl;
        exit(-1);
    }
    for(int i = 0; i < _nDim; i++)
        _data[i] = v[i];
}

void MyVector::set_position(const double* v)
{
    vector<double> tmp(v, v+_nDim);
    set_position(tmp);
}

double& MyVector::operator[](int v)
{
    return this->_data[v];
}

double MyVector::operator[](int v) const
{
    return this->_data[v];
}

void MyVector::operator=(const MyVector& v)
{
    this->set_dimension(v._nDim);
    for(int i=0; i<_nDim; i++)
    {
        this->_data[i] = v[i];
    }
}

MyVector MyVector::operator+=(const MyVector& v)
{
    if(_nDim == v._nDim)
    {
        for(int i=0; i< _nDim; i++)
            _data[i] += v[i];
        return *this;
    }
    else
    {
        cout << "MyVector::operator+= Error: the dimension of two vectors is different\n" << endl;
        exit(-1);
    }
}

MyVector MyVector::operator-=(const MyVector& v)
{
    if(_nDim == v._nDim)
    {
        for(int i=0; i< _nDim; i++)
            _data[i] -= v[i];
        return *this;
    }
    else
    {
        cout << "MyVector::operator-= Error: the dimension of two vectors is different\n" << endl;
        exit(-1);
    }
}

MyVector MyVector::operator+(const MyVector& v) const
{
    if(_nDim == v._nDim)
    {
        MyVector result(*this);
        result += v;
        return result;
    }
    else
    {
        cout << "MyVector::operator+ Error: the dimension of two vectors is different\n" << endl;
        exit(-1);
    }
}

MyVector MyVector::operator-(const MyVector& v) const
{
    if(_nDim == v._nDim)
    {
        MyVector result(*this);
        MyVector temp(v);
        temp = -temp;
        result += temp;
        return result;
    }
    else
    {
        cout << "MyVector::operator- Error: the dimension of two vectors is different\n" << endl;
        exit(-1);
    }
}

MyVector MyVector::operator-() const
{
    MyVector result(*this);
    for(auto &n:result._data)
        n = -n;
    return result;
}

MyVector MyVector::operator*(const double& v) const
{
    MyVector result(*this);
    result *= v;
    return result;
}

MyVector operator*(const double& v, const MyVector& vect)
{
    MyVector result(vect);
    result *= v;
    return result;
}

MyVector MyVector::operator*=(const double& v)
{
    for(auto &n:this->_data)
        n *= v;
    return *this;
}

MyVector MyVector::operator/(const double& v)
{
    MyVector result(*this);
    result /= v;
    return result;
}

MyVector MyVector::operator/=(const double& v)
{
    for(auto &n:this->_data)
        n/=v;
    return *this;
}

ostream& operator<<(ostream& os, const MyVector& v)
{
    os << '(';
    for(int i = 0; i<v._nDim; i++)
        if(i == v._nDim-1)
            os << v[i];
        else
            os << v[i] << ", ";
    os << ')';
    return os;
}

bool MyVector::operator==(const MyVector& v) const
{
    if(_nDim == v._nDim)
    {
        for(int i=0; i<_nDim; i++)
            if(this->_data[i] != v._data[i])
                return false;
        return true;
    }
    else
        return false;
}

bool MyVector::operator!=(const MyVector& v) const
{
    return !((*this) == v);
}

MyVector MyVector::normalize() const
{
    MyVector result(*this);
    result /= this->modulus();
    return result;
}

void MyVector::normalized()
{
    *this = this->normalize();
}

double MyVector::modulus() const
{
    double result = 0;
    for(auto n:this->_data)
        result += n*n;
    return sqrt(result);
}

void MyVector::set_modulus(const double& v)
{
    this->normalized();
    *this *= v;
}

double MyVector::dot_plus(const MyVector& v) const
{
    if(_nDim == v._nDim)
    {
        double result = 0;
        for(int i=0; i<_nDim; i++)
            result += _data[i] * v[i];
        return result;
    }
    else
    {
        cout << "MyVector::dot_plus Error: the dimension of two vectors is different\n";
        exit(-1);
    }
}

double MyVector::dot_plus(const MyVector& v1, const MyVector& v2)
{
    if(v1._nDim == v2._nDim)
    {
        double result = 0;
        for(int i=0;i<v1._nDim;i++)
            result += v1[i] * v2[i];
        return result;
    }
    else
    {
        cout << "MyVector::dot_plus Error: the dimension of two vectors is different\n";
        exit(-1);
    }
}

MyVector MyVector::cross_plus(const MyVector& v) const
{
    if(this->_nDim == 3 && v._nDim == 3)
    {
        MyVector result(3);
        result._data[0] = this->_data[1] * v._data[2] - this->_data[2] * v._data[1];
        result._data[1] = -(this->_data[0] * v._data[2] - this->_data[2] * v._data[0]);
        result._data[2] = this->_data[0] * v._data[1] - this->_data[1] * v._data[0];
        return result;
    }
    else
    {
        cout << "MyVector::cross_plus Error: the dimension of vectors should be 3\n";
        exit(-1);
    }
}

MyVector MyVector::cross_plus(const MyVector& v1, const MyVector& v2)
{
    if(v1._nDim == 3 && v2._nDim == 3)
        return v1.cross_plus(v2);
    else
    {
        cout << "MyVector::cross_plus Error: the dimension of vectors should be 3\n";
        exit(-1);
    }
}

double MyVector::angleBetween(const MyVector& v) const
{
    double result = 0;
    result = this->dot_plus(v) / (this->modulus() * v.modulus());
    return acos(result);
}

double MyVector::angleBetween(const MyVector& v1, const MyVector& v2)
{
    return v1.angleBetween(v2);
}

double MyVector::dist(const MyVector& v) const
{
    MyVector diff = *this - v;
    return diff.modulus();
}

double MyVector::dist(const MyVector& v1, const MyVector& v2)
{
    return v1.dist(v2);
}

void MyVector::random_vector()
{
    srand((unsigned long)time(nullptr));
    for(auto &n:this->_data)
        n = (double)(rand() % 10000);
    this->normalized();
}

MyVector MyVector::random_vector(int v)
{
    MyVector result(v);
    srand((unsigned long)time(nullptr));
    for(auto &n:result._data)
        n = (double)(rand() % 10000);
    result.normalized();
    return result;
}

