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

    矩阵的数形结合，就是坐标系转换
    几种特殊矩阵：
    单位矩阵：对角线为1，其余为0,单位矩阵是用矩阵表示某个坐标系的。
    [1 0 0
     0 1 0
     0 0 1]
    

## 坐标系转换
    极坐标、直角坐标系
    直角坐标系又分为：
        将手的拇指、食指、中指伸展开，互相垂直。 食指X、拇指Y、中指Z
        右手坐标系：
        左手坐标系：
    2维坐标系中
    [   cosb    -sinb
        sinb    cosb    ]
    说明：在原点为[0，0]的坐标系中，点A[x,y]。

    旋转矩阵：(顺时针b角度旋转后)
    1、未旋转前矩阵为
        [   1   -0
            0   1    ] 就是一个单位矩阵E，这里可以是2旋转矩阵的特殊情况，即b=0。
    A*E = A
    2、旋转后矩阵为
        [   cosb    -sinb
            sinb    cosb    ] R
    A*R = A'
    

    3维坐标系中
    旋转矩阵：
    x轴旋转矩阵：
    [   1   0       0
        0   cosb    -sinb
        0   sinb    cosb    ]
    y轴旋转矩阵：
    [   cosb    0   sinb
        0       1   0
        -sinb    0   cosb    ]
    z轴旋转矩阵：
    [   cosb    -sinb    0
        sinb    cosb    0
        0       0       1    ]


## Eigen3库学习

    描述矩阵行列 n x m n为行row m为列column
    矩阵 Matrix n x m
    向量 Vector n x 1
    
    矩阵相关概念
    1、转置:把矩阵A的行和列互相交换所产生的矩阵称为A的转置矩阵:matrix_name.transpose() 
        转置存在的原因，以3*n矩阵A为例，本意是表示n个三维点的集合，但是人们喜欢的输入方式为一个点一个点的输入，
            即x1y1z1 x2y2z2 ... xnynzn，矩阵就变成了n*3
        但是对点进行空间变换操作(乘以另外的一个n的方阵B)，因此需要转置A使之变成这个样子
        A(n*3).T() * B(n*n) = C(3*n)

    2、共轭:复数矩阵才存在，即将复数部分的符号取反:matrix_name.conjugate()
    
    3、共轭转置:复数矩阵才存在，把矩阵A的行和列互相交换,将复数部分的符号取反，然后再转置:matrix_name.adjoint()
    
    4、伴随:方阵A 的各元素的代数余子式Aij所构成的:Eigen没有直接的函数实现
    
    5、范数:用来衡量矩阵的大小和质量。包含多种不同的定义，
        1-范数就是矩阵元素绝对值之和:lpNorm<1>()
        2-范数就是矩阵的Frobenius范数，即矩阵元素平方和的平方根:matrix_name.norm()
        Infinity-范数就是矩阵元素绝对值中的最大值:lpNorm<Infinity>()
        lpNorm<x>() x为1表示1-范数，x为2表示2-范数，x为无穷表示无穷范数

    6、行列式:十字乘法
    
    7、逆矩阵:矩阵A的逆矩阵A^-1，满足A^-1 * A = I:matrix_name.inverse()。
            矩阵可逆的判定：
            1.先使用FullPivLU进行LU分解
            2.调用isInvertible函数，我们可以判断矩阵是否可逆。

    矩阵、向量间的乘法 A*B 满足A的行=B的列
    
    8、矩阵的秩：矩阵中线性无关的行或列的数目：matrix_name.rank()
    
    9、矩阵的迹：主对角线上的元素和：matrix_name.trace()
    
    10、设A为n阶方阵，若数  和n维的非零列向量x，使关系式Ax=λx成立，
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

    11、矩阵的奇异值：

    
    12、矩阵的块
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

    Eigen获取旋转矩阵
    1，初始化旋转向量：旋转角为alpha，旋转轴为(x,y,z)
    Eigen::AngleAxisd rotation_vector(alpha,Vector3d(x,y,z))
    2，旋转向量转旋转矩阵
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix=rotation_vector.matrix();

    Eigen::Matrix3d rotation_matrix;
    rotation_matrix=rotation_vector.toRotationMatrix();

### test示例ch2中的线性矩阵求解

    涉及知识：
    Ax=b 是否有解：
    用秩判断
    rank(A)=rank(A|b) 下面是对它的解释：
    Ax=b 就是判断b是否在A的列空间中，如果b在A的列空间中，那么Ax=b一定有解，反之则无解。
    rank表示维度
    eigen3表示A|b的增广矩阵：
    MatrixXd A(3, 3); // 假设A已经填充了数据
    VectorXd b(3); // 假设b已经填充了数据
    MatrixXd augmentedMatrix = MatrixXd::Zero(A.rows(), A.cols() + b.size()); // 创建一个全零的增广矩阵
    augmentedMatrix.block(0, 0, A.rows(), A.cols()) = A; // 将原矩阵A的数据复制到增广矩阵的相应位置
    augmentedMatrix.block(0, A.cols(), augmentedMatrix.rows(), b.size()) = b; // 将向量b的数据追加到增广矩阵的右侧


    1、矩阵的逆
    2、QR分解
    3、LU分解
    4、SVD分解


    Ax=b
    A =[
    v00 v01 v02
    v10 v11 v12
    v20 v21 v22]

    b = [
    b0 
    b1 
    b2]

    x = [
    x0 
    x1 
    x2]

    Ax=b 可以写作
    v00*x0+v01*x1+v02*x2=b0
    v10*x0+v11*x1+v12*x2=b1
    v20*x0+v21*x1+v22*x2=b2
    
    就是一个n线性的方程组求解。

    矩阵是否正定：

    矩阵A 标量λ 向量v 满足Av=λv，则称λ为A的特征值，v为A的特征向量。这里的坐标系说明是
    A表示一个坐标系 p[x,y,z]表示一个点
    λ表示 p点在A坐标系下的幅度变化
    v表示A坐标系下的相互垂直的向量
    SelfAdjointEigenSolver：Computes eigenvalues and eigenvectors of selfadjoint matrices. 计算自伴矩阵的特征值与特征矢量
    SelfAdjointEigenSolver::compute(A)  // 计算矩阵A的特征值和特征向量
    SelfAdjointEigenSolver::eigenvectors()  // 返回特征向量矩阵
    SelfAdjointEigenSolver::eigenvalues()  // 返回特征值向量

### Eigen提供的稠密矩阵分解

    https://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html

#### LU分解：将矩阵A分解为两个矩阵的乘积，L是一个下三角矩阵，U是一个上三角矩阵。
    A = LU
    上三角矩阵或者下三角矩阵，都是在开始的角只有一个非零0值，这样在乘以x的时候，就只有x的一个值存在，即
    构成 类似样子
    5x = 10
    1x + 2y = 6
    这样就有些类似之前解n元一次方程组一样了。

    LU分解的稳定性：因为浮点数的固有问题，在处理数值计算问题时候，一定要尽可能避免大数和小数相加减的问题。
    LUP分解：将矩阵A分解为三个矩阵的乘积，P是一个置换矩阵，L是一个下三角矩阵，U是一个上三角矩阵。
#### QR分解：将矩阵A分解为两个矩阵的乘积，Q是一个正交矩阵，R是一个上三角矩阵。
    A = QR
    正交矩阵：Q的转置矩阵等于Q的逆矩阵，即Q^T = Q^-1

#### LLT：标准Cholesky分解

    

