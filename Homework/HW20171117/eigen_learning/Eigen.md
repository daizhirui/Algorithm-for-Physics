# Eigen Learning Notes
[Official Wiki Link](http://eigen.tuxfamily.org/dox/)
---
---
[TOC]
## A. Dense matrix and array manipulation
### a. The Matrix class
1. The first three mandatory template parameters of Matrix are:

```cpp
Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
```
To define a matrix type:
```cpp
typedef Matrix<float, 4, 4> Matrix4f;
```
2. Vectors

**vectors are just a special case of matrices**
To define a vector type:
```cpp
typedef Matrix<float, 3, 1> Vector3f;       // column vector, most common
typedef Matrix<float, 1, 3> RowVector2f;    // row vector
```
3. The special value Dynamic

The dimensions of matrix or vector can be changed over time.
To define a matrix or a vector type whose dimension can be changed dynamically:
```cpp
typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
typedef Matrix<int, Dynamic, 1> VectorXi;
```
4. Coefficient accessors

The primary coefficient accessors and mutators in Eigen are the overloaded parenthesis operators.
```cpp
MatrixXd m(2,2);
m(0,0) = 3;
m(1,0) = 2.5;
m(0,1) = -1;
m(1,1) = m(1,0) + m(0,1);
```
5. Comma-initialization

Matrix and vector coefficients can be conveniently set using the so-called comma-initializer syntax.
```cpp
Matrix3f m;
m << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;
std::cout << m;
```

6. Resizing

The current size of a matrix can be retrieved by **rows()**, **cols()** and **size()**. These methods return the number of rows, the number of columns and the number of coefficients, respectively.
Resizing a dynamic-size matrix is done by the **resize()** method.
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
int main()
{
  MatrixXd m(2,5);
  m.resize(4,3);
  std::cout << "The matrix m is of size "
            << m.rows() << "x" << m.cols() << std::endl;
  std::cout << "It has " << m.size() << " coefficients" << std::endl;
  VectorXd v(2);
  v.resize(5);
  std::cout << "The vector v is of size " << v.size() << std::endl;
  std::cout << "As a matrix, v is of size "
            << v.rows() << "x" << v.cols() << std::endl;
}
```

- If you want a conservative variant of resize() which does not change the coefficients, use **conservativeResize()**.
- All these methods are still available on fixed-size matrices, for the sake of API uniformity. Of course, **you can't actually resize a fixed-size matrix**. Trying to change a fixed size to an actually different value will trigger an assertion failure

7. Assignment and resizing

**Assignment** is the action of copying a matrix into another, using **operator=**. Eigen resizes the matrix on the left-hand side automatically so that it matches the size of the matrix on the right-hand size.
Of course, if the left-hand side is of fixed size, resizing it is not allowed.

8. Fixed vs. Dynamic size
- Fixed size spends fixed size of memory to get higher performance, but sometimes, if the matrix is very huge, fixed size method should not be used because it is highly possible to result in stack overflow.
- Dynamic size is more flexible but has some influence on the performance.

9. Optional template parameters

Here is the complete list of template parameters:
```cpp
Matrix<typename Scalar,
       int RowsAtCompileTime,
       int ColsAtCompileTime,
       int Options = 0,
       int MaxRowsAtCompileTime = RowsAtCompileTime,
       int MaxColsAtCompileTime = ColsAtCompileTime>
```
We seldom use **Options**, ignore it.
**MaxRowsAtCompileTime** and **MaxColsAtCompileTime** are useful to avoid dynamic memory allocation when we know out matrix's max size over the whole computation.

10. Convenience typedefs

Eigen defines the following Matrix typedefs:

**MatrixNt** for Matrix<type, N, N>. For example, MatrixXi for Matrix<int, Dynamic, Dynamic>.
**VectorNt** for Matrix<type, N, 1>. For example, Vector2f for Matrix<float, 2, 1>.
**RowVectorNt** for Matrix<type, 1, N>. For example, RowVector3d for Matrix<double, 1, 3>.
Where:

**N** can be any one of 2, 3, 4, or X (meaning Dynamic).
**t** can be any one of i (meaning int), f (meaning float), d (meaning double), cf (meaning complex<float>), or cd (meaning complex<double>). The fact that typedefs are only defined for these five types **doesn't mean that they are the only supported scalar types**. For example, all standard integer types are supported.

### b. Matrix and vector arithmetic
About how to perform arithmetic between matrices, vectors and scalars with Eigen.

1. Addition and subtraction between Matrixs or vectors

```cpp
Matrix2d a,b;
Vector2d u,v;
...
// All the following expressions are OK.
a+b;
a-b;
-a;
a+=b;
a-=b;
u+v;
u-v;
u+=v;
u-=v;
```

2. Scalar multiplication and division
```cpp
Matrix2d a;
a << 1, 2,
     3, 4;
Vector3d v(1,2,3);
// All the following expressions are OK.
a * 2.5;    2.5 * a;
a *= 2.5;
a / 2.5;
a /= 2.5;
v * 2.5;    2.5 * v;
v *= 2.5;
v /= 2.5;
```

3. Transposition and conjugation

```cpp
MatrixXcf a = MatrixXcf::Random(2,2);
a.transpose();      // 转置
a.conjugation();    // 共轭
a.adjoint();        // 共轭转置
```
**WARNNING**
```cpp
a = a.transpose();
```
This kind of instruction will produce unexpected result.
```
Here is the matrix a:
1 2
3 4
and the result of the aliasing effect:
1 2
2 4
```
For in-place transposition, as for instance in a = a.transpose(), simply use the **transposeInPlace()** function:
```cpp
MatrixXf a(2,3); a << 1, 2, 3, 4, 5, 6;
cout << "Here is the initial matrix a:\n" << a << endl;
a.transposeInPlace();
cout << "and after being transposed:\n" << a << endl;
```
Output:
```
Here is the initial matrix a:
1 2 3
4 5 6
and after being transposed:
1 4
2 5
3 6
```

7. Matrix-matrix and matrix-vector multiplication

```cpp
Matrix2d mat1;
Matrix2d mat2;
Vector2d vet1;
Vector2d vet2;
// The following expressions are OK.
mat1 * mat2;
mat1 *= mat2;
mat1 * vet1;
vet1.transpose() * mat1;
vet1.transpose() * vet2;
```
Here we don't have to worry about something like **mat = mat * mat**
Eigen treats matrix multiplication as a special case and takes care of introducing a temporary here, so it will compile m=m*m as:
```cpp
tmp = m*m;
m = tmp;
```
If you know your matrix product can be safely evaluated into the destination matrix without aliasing issue, then you can use the noalias() function to avoid the temporary, e.g.:
```cpp
c.noalias() += a * b;
```

8. Dot product and cross product
For dot product and cross product, you need the **dot()** and **cross()** methods.
```cpp
Vector3d v(1,2,3);
Vector3d w(0,1,2);
v.dot(w);   // Dot product
v.cross(w); // Cross product
```
**Remember that cross product is only for vectors of size 3**

9. Basic arithmetic reduction operations

```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
int main()
{
  Eigen::Matrix2d mat;
  int i,j;
  mat << 1, 2,
         3, 4;
  cout << "Here is mat.sum():       " << mat.sum()       << endl;   // 元素求和
  cout << "Here is mat.prod():      " << mat.prod()      << endl;   // 元素求积
  cout << "Here is mat.mean():      " << mat.mean()      << endl;   // 元素平均
  cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << endl;   // 最小元素
  cout << "mat.minCoeff(&i, &j) returns the position"
  << '(' << i << ',' << j << ')' << endl;                   // 可以传两个指针来存该元素的位置
  cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << endl;   // 最大元素
  cout << "Here is mat.trace():     " << mat.trace()     << endl;   // 矩阵的迹（trace）
  cout << "Here is mat.diagonal().sum(): " << mat.diagonal().sum() << endl; // 矩阵的迹
}
```
Output:
```
Here is mat.sum():       10
Here is mat.prod():      24
Here is mat.mean():      2.5
Here is mat.minCoeff():  1
Here is mat.maxCoeff():  4
Here is mat.trace():     5
```

### c. The Array class and coefficient-wise operations
1. What is the Array class?

- provides an easy way to perform coefficient-wise operations
- no linear algebraic meaning, such as adding a constant to every coefficient in the array or multiplying two arrays coefficient-wise

2. Array types
The defition of Array types is similiar to Matrix types:
```cpp
// these are already provided by Eigen.
typedef Array<float, Dynamic, 1>        ArrayXf;
typedef Array<float, 3, 1>              Array3f;
typedef Array<double, Dynamic, Dynamic> ArrayXXd;
typedef Array<double, 3, 3>             Array33d;
```

3. Accessing values inside an Array:
via **operator(i, j)**, **i** is the column index and **j** is the row index.

4. Initilize an Array
Similar to the matrix, example:
```cpp
ArrayXXf m(2,2);
m(0,0) = 1.0; m(0,1) = 2.0;
m(1,0) = 3.0; m(1,1) = m(0,1) + m(1,0);
// Or:
m << 1.0, 2.0,
     3.0, 4.0;
```

5. Addition and subtraction

```cpp
ArrayXXf a(3,3);
ArrayXXf b(3,3);
a << 1,2,3,
    4,5,6,
    7,8,9;
b << 1,2,3,
    1,2,3,
    1,2,3;
a + b;
a - b;
a - 2;  // all coefficients are subtracted by 2.
```

6. Array multiplication

Where arrays are fundamentally different from matrices, is when you multiply two together. Matrices interpret multiplication as matrix product and arrays interpret multiplication as **coefficient-wise product**.
Example:
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
  ArrayXXf a(2,2);
  ArrayXXf b(2,2);
  a << 1,2,
       3,4;
  b << 5,6,
       7,8;
  cout << "a * b = " << endl << a * b << endl;
}
```
Output:
```cpp
a * b =
 5 12
21 32
```

7. Other coefficient-wise operations

**abs(), sqrt(), min(.)**
**min(.)**: to construct the array whose coefficients are the minimum of the corresponding coefficients of the two given arrays.
Example:
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
  ArrayXf a = ArrayXf::Random(5);
  a *= 2;
  cout << "a =" << endl
       << a << endl;
  cout << "a.abs() =" << endl
       << a.abs() << endl;
  cout << "a.abs().sqrt() =" << endl
       << a.abs().sqrt() << endl;
  cout << "a.min(a.abs().sqrt()) =" << endl
       << a.min(a.abs().sqrt()) << endl;
}
```
Output:
```
a =
  1.36
-0.422
  1.13
  1.19
  1.65
a.abs() =
 1.36
0.422
 1.13
 1.19
 1.65
a.abs().sqrt() =
1.17
0.65
1.06
1.09
1.28
a.min(a.abs().sqrt()) =
  1.17
-0.422
  1.06
  1.09
  1.28
```

8. Converting between array and matrix expressions

**Situation:**
If you need to do **linear algebraic operations** such as matrix multiplication, then you should use **matrices**; if you need to do **coefficient-wise operations**, then you should use **arrays**. However, sometimes it is not that simple, but you need to use both Matrix and Array operations.

**Solution A:**
In that case, **you need to convert a matrix to an array or reversely**.
**Matrix expressions** have an .**array()** method that 'converts' them into array expressions, so that coefficient-wise operations can be applied easily. Conversely, **array expressions** have a **.matrix()** method. As with all Eigen expression abstractions, this doesn't have any runtime cost (provided that you let your compiler optimize). **Both .array() and .matrix() can be used as rvalues and as lvalues**.

**Solution B:**
Assumpt that m and n are matrices, then some expressions like **m.array() * n.array()** can be rewriten as **m.cwiseProduct(n)**.

**Example:**
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
  MatrixXf m(2,2);
  MatrixXf n(2,2);
  MatrixXf result(2,2);
  m << 1,2,
       3,4;
  n << 5,6,
       7,8;
  result = m * n;
  cout << "-- Matrix m*n: --" << endl << result << endl << endl;
  result = m.array() * n.array();
  cout << "-- Array m*n: --" << endl << result << endl << endl;
  result = m.cwiseProduct(n);
  cout << "-- With cwiseProduct: --" << endl << result << endl << endl;
  result = m.array() + 4;
  cout << "-- Array m + 4: --" << endl << result << endl << endl;
}
```
Output:
```
-- Matrix m*n: --
19 22
43 50

-- Array m*n: --
 5 12
21 32

-- With cwiseProduct: --
 5 12
21 32

-- Array m + 4: --
5 6
7 8
```

### d. Block operations
A block is a rectangular part of a matrix or array. **Blocks expressions can be used both as rvalues and as lvalues**. As usual with Eigen expressions, this abstraction has zero runtime cost provided that you let your compiler optimize.

1. Using block operations: **.block()**
There are two versions:
```cpp
\\ Block of size(p,q), starting at (i,j)
\\ Version constructing a dynamic-size block expression
matrix.block(i,j,p,q);
\\ Version constructing a fixed-size block expression
matrix.block<p,q>(i,j);
```
**!! Bolcks expressions can also be used as lvalue**
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;
int main()
{
  Array22f m;
  m << 1,2,
       3,4;
  Array44f a = Array44f::Constant(0.6);
  cout << "Here is the array a:" << endl << a << endl << endl;
  a.block<2,2>(1,1) = m;
  cout << "Here is now a with m copied into its central 2x2 block:" << endl
   << a << endl << endl;
  a.block(0,0,2,3) = a.block(2,1,2,3);
  cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:"
  << endl << a << endl << endl;
}
```

2. Columns and rows
Individual columns and rows are special cases of blocks. Eigen provides methods to easily address them: **.col()** and **.row()**.

3. Corner-related operations
Eigen also provides special methods for blocks that are flushed against one of the corners or sides of a matrix or array. For instance, **.topLeftCorner()** can be used to refer to a block in the top-left corner of a matrix.

|Block operation|Version constructing a dynamic-size block expression|Version constructing a fixed-size block expression|
|---------------|----------------------------------------------------|--------------------------------------------------|
|Top-left p by q block *|matrix.topLeftCorner(p,q);|matrix.topLeftCorner\<p,q>();|
|Bottom-left p by q block *|matrix.bottomLeftCorner(p,q);|matrix.bottomLeftCorner\<p,q>();|
|Top-right p by q block *|matrix.topRightCorner(p,q);|matrix.topRightCorner\<p,q>();|
|Bottom-right p by q block *|matrix.bottomRightCorner(p,q);|matrix.bottomRightCorner\<p,q>();|
|Block containing the first q rows *|matrix.topRows(q);|matrix.topRows\<q>();|
|Block containing the last q rows *|matrix.bottomRows(q);|matrix.bottomRows\<q>();|
|Block containing the first p columns *|matrix.leftCols(p);|matrix.leftCols\<p>();|
|Block containing the last q columns *|matrix.rightCols(q);|matrix.rightCols\<q>();|

4. Block operations for vectors

|Block operation|Version constructing a dynamic-size block expression|Version constructing a fixed-size block expression|
|--|--|--|
|Block containing the first n elements *|vector.head(n);|vector.head\<n>();|
|Block containing the last n elements *|vector.tail(n);|vector.tail\<n>();|
|Block containing n elements, starting at position i *|vector.segment(i,n);|vector.segment\<n>(i);|

### e. Advanced initialization
1. The comma initilizer
```cpp
Matrix3f m;
m << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;
std::cout << m;
```

2. Special matrices and arrays
- **static method**
    - **Zero()**: initialize all coefficients to zero
    - **Constant(value)**: sets all coefficients to value
    - **Random()**: fills the matrix or array with random coefficients
    - **Identity()**: for matrix only, set it as identity matrix
    - **LinSpaced(size, low, high)**: only available for vectors and one-dimensional arrays; it yields a vector of the specified size whose coefficients are equally spaced between low and high.
    ```cpp
    ArrayXXf table(10, 4);
    table.col(0) = ArrayXf::LinSpaced(10, 0, 90);
    table.col(1) = M_PI / 180 * table.col(0);
    table.col(2) = table.col(1).sin();
    table.col(3) = table.col(1).cos();
    std::cout << "  Degrees   Radians      Sine    Cosine\n";
    std::cout << table << std::endl;
    ```
    Output:
    ```
    Degrees   Radians      Sine    Cosine
        0         0         0         1
       10     0.175     0.174     0.985
       20     0.349     0.342      0.94
       30     0.524       0.5     0.866
       40     0.698     0.643     0.766
       50     0.873     0.766     0.643
       60      1.05     0.866       0.5
       70      1.22      0.94     0.342
       80       1.4     0.985     0.174
       90      1.57         1 -4.37e-08
    ```
- Member functions
    - **setZero():**
    - **MatrixBase::setIdentity()**
    - **DenseBase::setLinSpaced()**

### f. Reductions, visitors and broadcasting
1. Norm computations 范数计算
[范数 from Zhihu.com](https://www.zhihu.com/question/20473040?utm_campaign=rss&utm_medium=rss&utm_source=rss&utm_content=title)
- **squaredNorm()**
- **norm()**
- **lpNorm()**: explanation:
$$m =
\left[
\begin{matrix}
a & b\\
c & d
\end{matrix}
\right]$$
$$m.lpNorm<q>=(a^q + b^q + c^q + d^q)^{\frac{1}{q}}$$
**Operator norm:** The 1-norm and $\infty$-norm matrix operator norms can easily be computed as follows:
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
  MatrixXf m(2,2);
  m << 1,-2,
       -3,4;
  cout << "1-norm(m)     = " << m.cwiseAbs().colwise().sum().maxCoeff()
       << " == "             << m.colwise().lpNorm<1>().maxCoeff() << endl;
  cout << "infty-norm(m) = " << m.cwiseAbs().rowwise().sum().maxCoeff()
       << " == "             << m.rowwise().lpNorm<1>().maxCoeff() << endl;
}
```
2. Boolean reductions
The following reductions operate on boolean values:
- **all()** returns true if **all of the coefficients** in a given Matrix or Array **evaluate to true** .
- **any()** returns true if **at least one** of the coefficients in a given Matrix or Array **evaluates to true** .
- **count()** returns **the number of coefficients** in a given Matrix or Array that **evaluate to true**.
- **array > q** is an Array of the same size as array, with true at those positions where the corresponding coefficient of array is greater than q.

3. **Partial reductions**<font color=#0099ff size=5>Partial reductions</font>
Partial reductions are reductions that can operate column- or row-wise on a Matrix or Array, applying the reduction operation on each column or row and returning a column or row vector with the corresponding values. **Partial reductions are applied with colwise() or rowwise()** .
    **Example1:**
    ```cpp
    #include <iostream>
    #include <Eigen/Dense>
    using namespace std;
    int main()
    {
        Eigen::MatrixXf mat(2,4);
        mat << 1, 2, 6, 9,
                3, 1, 7, 2;
        std::cout << "Column's maximum: " << std::endl
        << mat.colwise().maxCoeff() << std::endl;
    }
    ```
    **Example2:**
    ```cpp
    #include <iostream>
    #include <Eigen/Dense>
    using namespace std;
    using namespace Eigen;
    int main()
    {
        MatrixXf mat(2,4);
        mat << 1, 2, 6, 9,
               3, 1, 7, 2;

        MatrixXf::Index   maxIndex;
        float maxNorm = mat.colwise().sum().maxCoeff(&maxIndex);

        std::cout << "Maximum sum at position " << maxIndex << std::endl;
        std::cout << "The corresponding vector is: " << std::endl;
        std::cout << mat.col( maxIndex ) << std::endl;
        std::cout << "And its sum is is: " << maxNorm << std::endl;
    }
    // output:
    // Maximum sum at position 2
    // The corresponding vector is:
    // 6
    // 7
    // And its sum is is: 13
    ```
    **Example3:**
    ```cpp
    #include <iostream>
    #include <Eigen/Dense>
    using namespace std;
    int main()
    {
        Eigen::MatrixXf mat(2,4);
        Eigen::VectorXf v(2);

        mat << 1, 2, 6, 9,
                3, 1, 7, 2;
        v << 0,
             1;
        //add v to each column of m
        mat.colwise() += v;

        std::cout << "Broadcasting result: " << std::endl;
        std::cout << mat << std::endl;
    }
    // Output:
    // Broadcasting result:
    // 1 2 6 9
    // 4 2 8 3
    ```
    **Example4:**
    Now that broadcasting, reductions and partial reductions have been introduced, we can dive into a more advanced example that finds the nearest neighbour of a vector v within the columns of matrix m. The Euclidean distance will be used in this example, computing the squared Euclidean distance with the partial reduction named squaredNorm() :
    ```cpp
    #include <iostream>
    #include <Eigen/Dense>
    using namespace std;
    using namespace Eigen;
    int main()
    {
        Eigen::MatrixXf m(2,4);
        Eigen::VectorXf v(2);

        m << 1, 23, 6, 9,
            3, 11, 7, 2;

        v << 2,
            3;
        MatrixXf::Index index;
        // find nearest neighbour
        (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
        cout << "Nearest neighbour is column " << index << ":" << endl;
        cout << m.col(index) << endl;
    }
    // Output:
    // Nearest neighbour is column 0:
    // 1
    // 3
    ```
