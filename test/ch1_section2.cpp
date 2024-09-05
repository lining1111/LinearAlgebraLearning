//
// Created by lining on 9/5/24.
//
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

//矩阵加减
void AdditionAndSubtraction() {
    Matrix2d a;
    a << 1, 2, 3, 4;
    Matrix2d b;
    b << 5, 6, 7, 8;
    cout << "a + b = \n" << a + b << endl;
    cout << "a - b = \n" << a - b << endl;
}

//张量乘除
void ScalarMultiplicationAndDivision() {
    Matrix2d a;
    a << 1, 2, 3, 4;
    Vector3d v(1, 2, 3);
    cout << "a*2.5:\n" << a * 2.5 << endl;
    cout << "0.1*v:\n" << 0.1 * v << endl;
}

void ANoteAboutExpressionTemplates() {
    // 在Eigen中，诸如算术运算符（例如）operator+自己并不执行任何计算,
    // 它们仅返回描述要执行的计算的“表达式对象”。当计算整个表达式时，实际的计算将在稍后进行，
    // 通常在中operator=。尽管这听起来很沉重，但是任何现代的优化编译器都可以优化该抽象，从而获得完美优化的代码。例如，当您这样做时：

    // VectorXf a(50), b(50), c(50), d(50);
    // ...
    // a = 3*b + 4*c + 5*d;
    // Eigen将其编译为一个for循环，因此数组仅被遍历一次。简化（例如忽略SIMD优化），此循环如下所示：

    // 对于（int i = 0; i <50; ++ i）
    //   a [i] = 3 * b [i] + 4 * c [i] + 5 * d [i]；

    // 因此，您不必担心Eigen使用相对较大的算术表达式：它只会为Eigen提供更多优化机会。
}

// 矩阵转置、共轭、伴随
void TranspositionAndConjugation() {
    //矩阵或向量的转置$ a ^ T $，共轭$ \ bar {a} $和伴随（即共轭转置）分别通过成员函数transpose（），conjugate（）和adjoint（）获得
    MatrixXcf a(3, 3);
    a << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "Here is the matrix a\n" << a << endl;
    cout << "Here is the matrix a^T\n" << a.transpose() << endl;
    cout << "Here is the conjugate of a\n" << a.conjugate() << endl;
    cout << "Here is the adjoint of a\n" << a.adjoint() << endl;
    Matrix3f b(3, 3);
    b << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "adj:\n" << b.adjoint() << endl;
    FullPivLU<Matrix3f> lu(b);
    if (lu.isInvertible()) {
        cout << " here is the inverse of b\n" << b.inverse() << endl;
    }

    Matrix2f c(2, 2);
    c << 5, 8, 6, 9;
    auto d = c.determinant();
    cout << "det c = \n" << d << endl;
}

void MatrixMatrixAndMatrixVectorMultiplication() {
    Matrix2d mat;
    mat << 1, 2,
            3, 4;
    Vector2d u(-1, 1), v(2, 0);
    cout << "Here is mat*mat:\n"
         << mat * mat << endl;
    cout << "Here is mat*u:\n"
         << mat * u << endl;
    auto u_t = u.transpose();
    cout << "Here is u^T:\n" << u_t << endl;
    cout << "mat:\n" << mat << endl;
    cout << "Here is u^T*mat:\n"
         << u_t * mat << endl;
    cout << "Here is u^T*v:\n"
         << u.transpose() * v << endl;
    cout << "Here is u*v^T:\n"
         << u * v.transpose() << endl;
    cout << "Let's multiply mat by itself" << endl;
    mat = mat * mat;
    cout << "Now mat is mat:\n"
         << mat << endl;
}

void DotProductAndCrossProduct(){
    //叉积只适用于大小为3的向量，点积适用于任意向量
    Vector3d v(1, 2, 3);
    Vector3d w(0, 1, 2);
    cout << "Dot product: " << v.dot(w) << endl;
    double dp = v.adjoint() * w; // automatic conversion of the inner product to a scalar
    cout << "Dot product via a matrix product: " << dp << endl;
    cout << "Cross product:\n"
         << v.cross(w) << endl;
}

void BasicArithmeticReductionOperations(){
    Eigen::Matrix2d mat;
    mat << 1, 2,
            3, 4;
    //元素和，元素乘积，元素均值，最小系数，最大系数，迹
    cout << "Here is mat.sum():       " << mat.sum() << endl;
    cout << "Here is mat.prod():      " << mat.prod() << endl;
    cout << "Here is mat.mean():      " << mat.mean() << endl;
    cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
    cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
    cout << "Here is mat.trace():     " << mat.trace() << endl;

    // 可以返回元素位置
    Matrix3f m = Matrix3f::Random();
    std::ptrdiff_t i, j;
    float minOfM = m.minCoeff(&i, &j);
    cout << "Here is the matrix m:\n"
         << m << endl;
    cout << "Its minimum coefficient (" << minOfM
         << ") is at position (" << i << "," << j << ")\n\n";
    RowVector4i v = RowVector4i::Random();
    int maxOfV = v.maxCoeff(&i);
    cout << "Here is the vector v: " << v << endl;
    cout << "Its maximum coefficient (" << maxOfV
         << ") is at position " << i << endl;
}

void ValidityOfoperations(){
    // Eigen的输出很操蛋，但是它把输出中关键的信息大写了～
    // 如果你想体验一下Eigen的错误输出，则注释掉下面的内容

    // Matrix3f m;
    // Vector4f v;
    // v = m * v; // Compile-time error: YOU_MIXED_MATRICES_OF_DIFFERENT_SIZES

    // {
    //         MatrixXf m(3, 3);
    //         VectorXf v(4);
    //         v = m * v; // Run-time assertion failure here: "invalid matrix product"
    // }
}

int main() {
//    AdditionAndSubtraction();
//    ScalarMultiplicationAndDivision();
//    TranspositionAndConjugation();
    MatrixMatrixAndMatrixVectorMultiplication();
    return 0;
}