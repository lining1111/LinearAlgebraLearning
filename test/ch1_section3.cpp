//
// Created by lining on 9/5/24.
//

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

void AccessingValuesInsideAnArray() {
    ArrayXXf m(2, 2); // 二维动态float类型数组

    // assign some values coefficient by coefficient
    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 0) = 3.0;
    m(1, 1) = m(0, 1) + m(1, 0);

    // print values to standard output
    cout << m << endl
         << endl;

    // using the comma-initializer is also allowed
    m << 1.0, 2.0, 3.0, 4.0;

    // print values to standard output
    cout << m << endl;
}

void AdditionAndSubtraction() {
    // 加减法
    // 两个数组的加减法与矩阵相同。
    // 如果两个数组的大小相同，并且该加法或减法是按系数进行的，则此操作有效。
    // 数组还支持以下形式的表达式，该表达式array + scalar将标量添加到数组中的每个系数。
    // 这提供了不能直接用于Matrix对象的功能。
    ArrayXXf a(3, 3);
    ArrayXXf b(3, 3);
    a << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    b << 1, 2, 3,
            1, 2, 3,
            1, 2, 3;

    // Adding two arrays
    cout << "a + b = " << endl
         << a + b << endl
         << endl;
    // Subtracting a scalar from an array
    cout << "a - 2 = " << endl
         << a - 2 << endl;
}

void ArrayMultiplication() {
    //您可以将一个数组乘以标量，这与矩阵的工作方式相同。
    //数组与矩阵根本不同的地方是将两个矩阵相乘。
    //矩阵将乘法解释为矩阵乘积，而数组将乘法解释为按系数乘积。
    //因此，当且仅当两个数组具有相同的维数时，它们才能相乘
    ArrayXXf a(2, 2);
    ArrayXXf b(2, 2);
    a << 1, 2,
            3, 4;
    b << 5, 6,
            7, 8;
    cout << "a * b = " << endl
         << a * b << endl;
}

void OtherCoefficientwiseOperations() {
    // 数组类定义除上述加法，减法和乘法运算符其他系数为单位的运算。
    // 例如，.abs()方法获取每个系数的绝对值，而.sqrt（）计算系数的平方根。
    //如果您有两个大小相同的数组，则可以调用.min()来构造其系数是两个给定数组中对应系数的最小值的数组。
    //注意:.array()和.matrix() 转换为相同的维数，但是不同的对象具有不同的方法
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

void ConvertingBetweenArrayAndMatrixExpressions() {
    // 什么时候应该使用Matrix类的对象，什么时候应该使用Array类的对象？
    //您不能对数组应用矩阵运算，也不能对矩阵应用数组运算。
    //因此，如果您需要进行线性代数运算（例如矩阵乘法），则应使用矩阵。
    //如果需要进行系数运算，则应使用数组。
    //但是，有时并不是那么简单，但是您需要同时使用Matrix和Array操作。
    //在这种情况下，您需要将矩阵转换为数组或反向转换。无论选择将对象声明为数组还是矩阵，都可以访问所有操作。
    // 矩阵表达式具有.array()方法，可以将它们“转换”为数组表达式，因此可以轻松地应用按系数进行运算。
    //相反，数组表达式具有.matrix()方法。
    //与所有Eigen表达式抽象一样，这没有任何运行时开销（只要您让编译器进行优化）
    //.array（）和.matrix() 可被用作右值和作为左值。

    // Eigen禁止在表达式中混合矩阵和数组。
    // 例如，您不能直接矩阵和数组相加。运算符+的操作数要么都是矩阵，要么都是数组。
    //但是，使用.array（）和.matrix（）可以轻松地将其转换为另一种。

    //～～～～注意～～～～～
    //此规则的例外是赋值运算符=：允许将矩阵表达式分配给数组变量，或将数组表达式分配给矩阵变量。

    // 下面的示例演示如何通过使用.array（）方法对Matrix对象使用数组操作。
    // 例如，语句需要两个矩阵和，他们两个转换为阵列，用来将它们相乘系数明智并将结果指定给矩阵变量（这是合法的，因为本征允许分配数组表达式到矩阵的变量）。result = m.array() * n.array()mnresult

    // 实际上，这种使用情况非常普遍，以至于Eigen为矩阵提供了const .cwiseProduct()方法来计算系数乘积。
    MatrixXf m(2, 2);
    MatrixXf n(2, 2);
    MatrixXf result(2, 2);
    m << 1, 2,
            3, 4;
    n << 5, 6,
            7, 8;
    result = m * n;
    cout << "-- Matrix m*n: --" << endl
         << result << endl
         << endl;
    result = m.array() * n.array();
    cout << "-- Array m*n: --" << endl
         << result << endl
         << endl;
    result = m.cwiseProduct(n);
    cout << "-- With cwiseProduct: --" << endl
         << result << endl
         << endl;
    result = m.array() + 4;
    cout << "-- Array m + 4: --" << endl
         << result << endl
         << endl;
}


int main() {
    AccessingValuesInsideAnArray();

    return 0;
}