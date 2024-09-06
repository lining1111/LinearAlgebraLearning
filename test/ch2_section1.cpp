//
// Created by lining on 9/6/24.
//
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

/**
 * A*x=b 求x
 */
void BasicLinearSolving() {
    Matrix3d A;
    A << 1, 2, 3,
            4, 5, 6,
            7, 8, 10;

    Vector3d b(3, 3, 4);

    cout << "A = \n" << A << endl;
    cout << "b = \n" << b << endl;
    //在此示例中，colPivHouseholderQr（）方法返回类ColPivHouseholderQR的对象。
    //由于此处的矩阵类型为Matrix3f，因此该行可能已替换为：
    //ColPivHouseholderQR <Matrix3f> dec（A）;
    //Vector3f x = dec.solve（b）;
    //在这里，ColPivHouseholderQR是具有选择列主元功能的QR分解。
    Vector3d x = A.colPivHouseholderQr().solve(b);
//    Vector3d x = A.inverse() * b;
    cout << "x = " << x.transpose() << endl;

    {
        //所有这些分解都提供了一个solve（）方法，该方法与上述示例一样。
        //例如，如果您的矩阵是正定的，则上表说明LLT或LDLT分解是一个很好的选择。这是一个示例，也说明使用通用矩阵（而非矢量）作为右手边是可能的。
        Matrix2f A, b;
        A << 2, -1, -1, 3;
        b << 1, 2, 3, 1;
        cout << "Here is the matrix A:\n"
             << A << endl;
        cout << "Here is the right hand side b:\n"
             << b << endl;
        Matrix2f x = A.ldlt().solve(b);
        cout << "The solution is:\n"
             << x << endl;
        //Output is:
        // Here is the matrix A:
        //  2 -1
        // -1  3
        // Here is the right hand side b:
        // 1 2
        // 3 1
        // The solution is:
        // 1.2 1.4
        // 1.4 0.8

        // Eigen 矩阵分解：http://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html
    }
}

void CheckingIfASolutionReallyExists() {
    //计算相对误差的方法
    //只有您知道要允许解决方案被视为有效的误差范围。因此，Eigen允许您自己进行此计算，如以下示例所示：
    MatrixXd A = MatrixXd::Random(100, 100);
    MatrixXd b = MatrixXd::Random(100, 50);
    MatrixXd x = A.fullPivLu().solve(b);
    double relative_error = (A * x - b).norm() / b.norm(); // norm() is L2 norm
    cout << "The relative error is:\n"
         << relative_error << endl;
}

void LeastSquaresSolving() {
    //最小二乘求解的最准确方法是SVD分解。Eigen提供了两种实现。
    //推荐的对象是BDCSVD类，它可以很好地解决较大的问题，并自动退回到JacobiSVD类以解决较小的问题。
    //对于这两个类，它们的resolve（）方法都在进行最小二乘求解。
    MatrixXd A = MatrixXd::Random(3, 2);
    VectorXd b = VectorXd::Random(3);
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the right hand side b:\n" << b << endl;
    MatrixXd x = A.bdcSvd(ComputeThinU | ComputeThinV).solve(b);
    cout << "The least-squares solution is:\n"
         << x << endl;
}

void ComputingEigenvaluesAndEigenvectors() {
    //您需要在此处进行特征分解， 确保检查矩阵是否是自伴随的，
    //在数学里，作用于一个有限维的内积空间，一个自伴算子(self-adjoint operator)等于自己的伴随算子；
    // 等价地说，表达自伴算子的矩阵是埃尔米特矩阵。埃尔米特矩阵等于自己的共轭转置。
    // 根据有限维的谱定理，必定存在着一个正交归一基，可以表达自伴算子为一个实值的对角矩阵。
    // 就像在这些问题中经常发生的那样。这是一个使用SelfAdjointEigenSolver的示例，
    // 可以使用EigenSolver或ComplexEigenSolver轻松地将其应用于一般矩阵。
    //特征值和特征向量的计算不一定会收敛，但是这种收敛失败的情况很少。调用info()就是为了检查这种可能性。

    Matrix2f A;
    A << 1, 2, 2, 3;
    cout << "Here is the matrix A:\n"
         << A << endl;
    SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
    if (eigensolver.info() != Success)
        abort();
    cout << "The eigenvalues of A are:\n"
         << eigensolver.eigenvalues() << endl;
    cout << "Here's a matrix whose columns are eigenvectors of A \n"
         << "corresponding to these eigenvalues:\n"
         << eigensolver.eigenvectors() << endl;
    //Output is:
    // Here is the matrix A:
    // 1 2
    // 2 3
    // The eigenvalues of A are:
    // -0.236
    //   4.24
    // Here's a matrix whose columns are eigenvectors of A
    // corresponding to these eigenvalues:
    // -0.851 -0.526
    //  0.526 -0.851

}

void ComputingInverseAndDeterminant() {
    //首先，请确保您确实想要这个。尽管逆和行列式是基本的数学概念，但在数值线性代数中，它们不如在纯数学中流行。
    //逆计算通常可以用solve（）操作代替，而行列式通常不是检查矩阵是否可逆的好方法。
    //但是，对于非常 小的矩阵，上述条件是不正确的，并且逆和行列式可能非常有用。
    //尽管某些分解（例如PartialPivLU和FullPivLU）提供了inverse（）和determinant（）方法，
    //但您也可以直接在矩阵上调用inverse（）和determinant（）。
    //如果矩阵的固定大小很小（最多为4x4），这将使Eigen避免执行LU分解，而应使用对此类小矩阵更有效的公式。
    Matrix3f A;
    A << 1, 2, 1,
            2, 1, 0,
            -1, 1, 2;
    cout << "Here is the matrix A:\n"
         << A << endl;
    cout << "The determinant of A is " << A.determinant() << endl;
    cout << "The inverse of A is:\n"
         << A.inverse() << endl;

    // Output is:
    // Here is the matrix A:
    //  1  2  1
    //  2  1  0
    // -1  1  2
    // The determinant of A is -3
    // The inverse of A is:
    // -0.667      1  0.333
    //   1.33     -1 -0.667
    //     -1      1      1

}

void SeparatingTheComputationFromTheConstruction() {
    // 在以上示例中，在构造分解对象的同时计算了分解。但是，在某些情况下，您可能希望将这两件事分开，
    //例如，如果在构造时不知道要分解的矩阵，则可能会需要将它们分开。或者您想重用现有的分解对象。
    // 使之成为可能的原因是：
    // 所有分解都有默认的构造函数，
    // 所有分解都具有执行计算的compute（matrix）方法，并且可以在已计算的分解中再次调用该方法，以将其重新初始化。
    Matrix2f A, b;
    LLT<Matrix2f> llt;
    A << 2, -1, -1, 3;
    b << 1, 2, 3, 1;
    cout << "Here is the matrix A:\n"
         << A << endl;
    cout << "Here is the right hand side b:\n"
         << b << endl;
    cout << "Computing LLT decomposition..." << endl;
    llt.compute(A);
    cout << "The solution is:\n"
         << llt.solve(b) << endl;
    A(1, 1)++;
    cout << "The matrix A is now:\n"
         << A << endl;
    cout << "Computing LLT decomposition..." << endl;
    llt.compute(A);
    cout << "The solution is now:\n"
         << llt.solve(b) << endl;
    //最后，您可以告诉分解构造函数预先分配存储空间以分解给定大小的矩阵，以便在随后分解此类矩阵时，不执行动态内存分配（当然，如果您使用的是固定大小的矩阵，则不存在动态内存分配完全发生）。
    //只需将大小传递给分解构造函数即可完成，如以下示例所示：
    {
        HouseholderQR<MatrixXf> qr(50, 50);
        MatrixXf A = MatrixXf::Random(50, 50);
        qr.compute(A); //没有动态内存分配
    }

}

void RankRevealingDecompositions() {
    //某些分解是揭示矩阵秩的。
    //这些通常也是在非满秩矩阵（在方形情况下表示奇异矩阵）的情况下表现最佳的分解。
    //秩揭示分解至少提供了rank()方法。它们还可以提供方便的方法，例如isInvertible()，
    //并且还提供一些方法来计算矩阵的核（零空间）和像（列空间），就像FullPivLU那样：
    Matrix3f A;
    A << 1, 2, 5,
            2, 1, 4,
            3, 0, 3;
    cout << "Here is the matrix A:\n"
         << A << endl;
    FullPivLU<Matrix3f> lu_decomp(A);
    cout << "The rank of A is " << lu_decomp.rank() << endl;
    cout << "Here is a matrix whose columns form a basis of the null-space of A:\n"
         << lu_decomp.kernel() << endl;
    cout << "Here is a matrix whose columns form a basis of the column-space of A:\n"
         << lu_decomp.image(A) << endl; // yes, have to pass the original A

    // Output is:
    // Here is the matrix A:
    // 1 2 5
    // 2 1 4
    // 3 0 3
    // The rank of A is 2
    // Here is a matrix whose columns form a basis of the null-space of A:
    //  0.5
    //    1
    // -0.5
    // Here is a matrix whose columns form a basis of the column-space of A:
    // 5 1
    // 4 2
    // 3 3

    //当然，任何秩计算都取决于对任意阈值的选择，因为实际上没有浮点矩阵恰好是秩不足的。
    //Eigen选择一个明智的默认阈值，该阈值取决于分解，但通常是对角线大小乘以机器ε。
    //虽然这是我们可以选择的最佳默认值，但只有您知道您的应用程序的正确阈值是多少。
    //您可以通过在调用rank（）或需要使用此阈值的任何其他方法之前在分解对象上调用setThreshold（）来进行设置。
    //分解本身（即compute（）方法）与阈值无关。更改阈值后，无需重新计算分解.
    {
        Matrix2d A;
        A << 2, 1,
                2, 0.9999999999;
        FullPivLU<Matrix2d> lu(A);
        cout << "By default, the rank of A is found to be " << lu.rank() << endl;
        lu.setThreshold(1e-5);
        cout << "With threshold 1e-5, the rank of A is found to be " << lu.rank() << endl;

        // Output is:
        // By default, the rank of A is found to be 2
        // With threshold 1e-5, the rank of A is found to be 1
    }
}


int main() {
    BasicLinearSolving();

    return 0;
}