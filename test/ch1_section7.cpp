//
// Created by lining on 9/6/24.
//
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

void Reshape() {
    // 重塑
    //整形操作在于修改矩阵的大小，同时保持相同的系数。
    //除了修改输入矩阵本身（这对于编译时大小而言是不可能的）之外，
    //该方法还包括使用Map类在存储上创建不同的视图。这是创建矩阵的一维线性视图的典型示例：
    MatrixXf M1(3, 3); // Column-major storage
    M1 << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    Map<RowVectorXf> v1(M1.data(), M1.size()); // v1 is a row vector of size 9
    cout<< "v1 = \n" << v1 << endl;
    Matrix<float,Dynamic,Dynamic,RowMajor> M2(M1); // M2 is a column vector of size 9
    Map<RowVectorXf> v2(M2.data(), M2.size()); // v2 is a row vector of size 9
    cout<< "v2 = \n" << v2 << endl;

    //注意输入矩阵的存储顺序如何修改线性视图中系数的顺序。这是另一个将2x6矩阵重塑为6x2矩阵的示例：
    {
        MatrixXf M1(2, 6); // Column-major storage
        M1 << 1, 2, 3, 4, 5, 6,
                7, 8, 9, 10, 11, 12;
        Map<MatrixXf> M2(M1.data(), 6, 2);
        cout << "M2:" << endl
             << M2 << endl;
        //Output is:
        //  M2:
        //  1  4
        //  7 10
        //  2  5
        //  8 11
        //  3  6
        //  9 12
    }

}

void Slicing(){
    //切片包括获取一组在矩阵内均匀间隔的行，列或元素。再次，Map类可以轻松模仿此功能。
    //例如，可以跳过向量中的每个P元素：
    RowVectorXf v = RowVectorXf::LinSpaced(20, 0, 19);
    cout << "Input:" << endl
         << v << endl;
    Map<RowVectorXf, 0, InnerStride<2>> v2(v.data(), v.size() / 2);
    cout << "Even:" << v2 << endl;
    //Output is:
    //  Input:
    //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
    // Even: 0  2  4  6  8 10 12 14 16 18

    //一个人可以根据实际的存储顺序，使用适当的外步幅或内步幅来占据三列中的一列：
    MatrixXf M1 = MatrixXf::Random(3, 8);
    cout << "Column major input:" << endl
         << M1 << "\n";
    Map<MatrixXf, 0, OuterStride<>> M2(M1.data(), M1.rows(), (M1.cols() + 2) / 3, OuterStride<>(M1.outerStride() * 3));
    cout << "1 column over 3:" << endl
         << M2 << "\n";
    typedef Matrix<float, Dynamic, Dynamic, RowMajor> RowMajorMatrixXf;
    RowMajorMatrixXf M3(M1);
    cout << "Row major input:" << endl
         << M3 << "\n";
    Map<RowMajorMatrixXf, 0, Stride<Dynamic, 3>> M4(M3.data(), M3.rows(), (M3.cols() + 2) / 3,
                                                    Stride<Dynamic, 3>(M3.outerStride(), 3));
    cout << "1 column over 3:" << endl
         << M4 << "\n";
    //Column major input:
    //    0.68   0.597   -0.33   0.108   -0.27   0.832  -0.717  -0.514
    //  -0.211   0.823   0.536 -0.0452  0.0268   0.271   0.214  -0.726
    //   0.566  -0.605  -0.444   0.258   0.904   0.435  -0.967   0.608
    // 1 column over 3:
    //    0.68   0.108  -0.717
    //  -0.211 -0.0452   0.214
    //   0.566   0.258  -0.967
    // Row major input:
    //    0.68   0.597   -0.33   0.108   -0.27   0.832  -0.717  -0.514
    //  -0.211   0.823   0.536 -0.0452  0.0268   0.271   0.214  -0.726
    //   0.566  -0.605  -0.444   0.258   0.904   0.435  -0.967   0.608
    // 1 column over 3:
    //    0.68   0.108  -0.717
    //  -0.211 -0.0452   0.214
    //   0.566   0.258  -0.967
}


int main() {
    Reshape();
    return 0;
}