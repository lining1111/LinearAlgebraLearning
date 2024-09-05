//
// Created by lining on 9/4/24.
//
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void CoefficientAccessors() {
    //定义矩阵大小，但未初始化，该方式在堆上分配内存
    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    cout << m << endl;
}

void MatrixAndVectorRunTime() {
    //固定大小的矩阵or向量在栈上分配内存，因为它在编译时期就可以确定大小
    //MatrixX表示运行时才确定矩阵的大小，因为它在堆上分配内存
    MatrixXd m = MatrixXd::Random(3, 3);
    m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
    cout << "m:"<< endl;
    cout << m << endl;
    VectorXd v(3);
    v << 1, 2, 3;
    cout << "v:"<< endl;
    cout << v << endl;
}
void MatrixAndVectorCompileTime()
{
    // 编译时可确定矩阵尺寸，在栈上分配内存
    Matrix3d m = Matrix3d::Random(); //a fixed size
    m = (m + Matrix3d::Constant(1.2)) * 50;
    cout << "m =" << endl
         << m << endl;
    Vector3d v(1, 2, 3);

    cout << "m * v =" << endl
         << m * v << endl;
}

void AssignmentAndResizing(){
    //operator= 将矩阵复制到另一个矩阵中的操作。Eigen自动调整左侧矩阵的大小，使其与右侧大小的矩阵大小匹配
    MatrixXf a(2,2);
    cout << "a is of size " << a.rows() << "x" << a.cols() << endl;
    MatrixXf b(3, 3);
    a = b;
    cout << "a is now of size " << a.rows() << "x" << a.cols() << endl;
}

void ConvenienceTypedefs(){
    // Eigen定义了以下Matrix typedef：

    // MatrixNt for Matrix<type, N, N>. For example, MatrixXi for Matrix<int, Dynamic, Dynamic>.
    // VectorNt for Matrix<type, N, 1>. For example, Vector2f for Matrix<float, 2, 1>.
    // RowVectorNt for Matrix<type, 1, N>. For example, RowVector3d for Matrix<double, 1, 3>.
    // Where:
    // N可以是任何一个2，3，4，或X（意思Dynamic）。
    // t可以是i（表示int），f（表示float），d（表示double），cf（表示complex <float>）或cd（表示complex <double>）的任何一种。
    //仅针对这五个类型定义typedef的事实并不意味着它们是唯一受支持的标量类型。例如，支持所有标准整数类型，请参阅标量类型。
}



int main() {
//    CoefficientAccessors();
//    MatrixAndVectorRunTime();
//    MatrixAndVectorCompileTime();
    AssignmentAndResizing();

    return 0;
}