## C++ 版本的线性代数学习

    目的：主要通过Eigen库以及OpenCV库来学习线性代数
    Eigen库，主要用来学习矩阵运算，用于雷达数据的坐标系转换
    OpenCV库，主要用来学习图像处理，用于图像坐标系的转换

    矩阵相关数据类型
    Eigen:
    Matrix<type, rows, cols> matrix_name(rows, cols)
    Vector<type, size> vector_name(size)
    MatrixXd matrix_name(rows, cols)
    VectorXd vector_name(size)
    OpenCV:
    cv::Mat matrix_name(rows, cols, type)
    cv::Mat_<type> matrix_name(rows, cols)
    cv::Matx<type, rows, cols> matrix_name(rows, cols)
    cv::Vec<type, size> vector_name(size)
    cv::Scalar<type> scalar_name

## Eigen3库学习

    描述矩阵行列 n x m n为行row m为列column
    矩阵 Matrix n x m
    向量 Vector n x 1
    
    矩阵
    转置,把矩阵A的行和列互相交换所产生的矩阵称为A的转置矩阵:matrix_name.transpose() 
    共轭，复数矩阵才存在，即将复数部分的符号取反:matrix_name.conjugate()
    共轭转置，复数矩阵才存在，把矩阵A的行和列互相交换,将复数部分的符号取反，然后再转置:matrix_name.adjoint()
    伴随，方阵A 的各元素的代数余子式Aij所构成的:Eigen没有直接的函数实现
    行列式，十字乘法
    逆矩阵，矩阵A的逆矩阵A^-1，满足A^-1 * A = I:matrix_name.inverse()。
            矩阵可逆的判定：
            1.先使用FullPivLU进行LU分解
            2.调用isInvertible函数，我们可以判断矩阵是否可逆。

    矩阵、向量间的乘法 A*B 满足A的行=B的列
    矩阵的秩：矩阵中线性无关的行或列的数目：matrix_name.rank()
    矩阵的迹：主对角线上的元素和：matrix_name.trace()
    设A为n阶方阵，若数  和n维的非零列向量x，使关系式Ax=λx成立，
    则称数λ为方阵A的特征值，非零向量x称为A的对应与特征值λ的特征向量。
    矩阵的特征向量：EigenSolver eigenvectors
    矩阵的特征值： EigenSolver eigenvalues
         // 创建一个4x4的随机矩阵
        MatrixXd K = MatrixXd::Random(4, 4);
        // 使用EigenSolver计算特征值和特征向量
        EigenSolver<MatrixXd> es(K);
        // 获取特征向量
        MatrixXd evecs = es.eigenvectors();
        // 获取特征值
        VectorXd evals = es.eigenvalues();

    矩阵的奇异值：

    矩阵的块
    //前言：
    //块是矩阵或数组的某一部分。块表达式既可以用作右值，也可以用作左值。
    // Block operation
    // Block of size (p,q), starting at (i,j)
    
    //Version constructing a  dynamic-size block expression
    // 起始位置+行列数
    // matrix.block(i,j,p,q);
    
    //Version constructing a fixed-size block expression
    // 模板参数为行列数，函数参数为起始位置
    // matrix.block<p,q>(i,j);
    
    //两种版本均可用于固定大小和动态大小的矩阵和数组。
    //这两个表达式在语义上是等效的。
    //唯一的区别是，如果块大小较小，则固定大小版本通常会为您提供更快的代码，但是需要在编译时知道此大小。