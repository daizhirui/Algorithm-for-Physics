# MyVector

## Introduction
MyVector is a math class supporting the basic calculation of vector.
The class is achieved in ___MyVector.cpp___ and ___MyVector.h___
The test program is achieved in ___testMyVector.cpp___, which shows some examples of using this class.

## Compile and test

```bash
make            # compile MyVector as a static library and compile testMyVector
make lib        # compile MyVector as a static library
make test       # run testMyVector to test this class
make clean      # clean *.a *.o files
make cleanall   # clean *.a *.o and the exec bin
```

## History
- 2017-11-03
    - first release, basic functions completed
- 2017-11-10
    - add operator[], dot, cross
- 2017-11-17
    - add angleBetween, dist, random_vector
- 2017-11-18
    - add operator==, operator!=, operator-(negative sign)
- 2017-11-19
    - try to add rotate functions, common usage unknown
- 2017-11-20
    - stop the development of rotate functions
    - complete the test program
- 2017-11-27
    - update the makefile
    - project completed, upload to the server
- 2017-11-30
    - correct the name of dot() and cross()

## Member functions

### Construct functions

```cpp
MyVector::MyVector();
MyVector::MyVector(int);
MyVector::MyVector(int, const vector<double>&);
MyVector::MyVector(int, const double*);
MyVector::MyVector(const MyVector&);
```
### Deconstruct function

```cpp
MyVector::~MyVector();
```
### Dimension setup functions

```cpp
void MyVector::set_dimension(int);
int MyVector::dimension();
```
### Position setup functions

```cpp
void MyVector::set_position(const vector<double>&);
void MyVector::set_position(const double*);
```

### operator

```cpp
double& MyVector::operator[](int);
double MyVector::operator[](int) const;
void MyVector::operator=(const MyVector&);
MyVector MyVector::operator+(const MyVector&) const;
MyVector MyVector::operator-(const MyVector&) const;
MyVector MyVector::operator-() const;
MyVector MyVector::operator*(const double&) const;
friend MyVector operator*(const double&, const MyVector&);
MyVector MyVector::operator/(const double&);
MyVector MyVector::operator+=(const MyVector&);
MyVector MyVector::operator-=(const MyVector&);
MyVector MyVector::operator*=(const double&);
MyVector MyVector::operator/=(const double&);
friend ostream& operator<<(ostream&, const MyVector&);
bool MyVector::operator==(const MyVector&) const;
bool MyVector::operator!=(const MyVector&) const;
```

### Calculation functions

```cpp
MyVector MyVector::normalize() const;
void MyVector::normalized();
double MyVector::modulus() const;
void MyVector::set_modulus(const double&);
double MyVector::dot(const MyVector&) const;
static double MyVector::dot(const MyVector&, const MyVector&);
MyVector MyVector::cross(const MyVector&) const;
static MyVector::MyVector cross(const MyVector&, const MyVector&);
double MyVector::angleBetween(const MyVector&) const;
static double MyVector::angleBetween(const MyVector&, const MyVector&);
double MyVector::dist(const MyVector&) const;
static MyVector::double dist(const MyVector&, const MyVector&);
```

### Other functions

```cpp
void MyVector::random_vector();
static MyVector MyVector::random_vector(int);
```

