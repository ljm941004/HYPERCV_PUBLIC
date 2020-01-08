
高维度遥感图像处理库 HyperCV 项目概述
____________________________________________

高维度遥感数据是一种数据立方体例如高光谱多光谱等。

这个库集成了遥感图像处理中可能用到的大部分函数。

以及影像遥感领域常用算法。

HYPERCV model 模块中有5个文件夹。

1. core中是存放核心的声明以及框架函数。
(1) hypermat.c               高光谱图像结构体， 读取、存储高光谱、多光谱图像。
(2) simplemat.c              二维图像结构体，读取、存储二维图像。
(3) struct_2D.c              二维处理核结构体，用于滤波等图像处理核。
(4) vector.c                 C语言实现可变向量数组。

2. process中是数据处理模块,包括高光谱、多光谱和二维数据图像。
(1) colortransform.c         rgb2gray gray2rgb
(2) datatypechange.c         uchar short float int 等图像数据类型转换
(3) filter.c                 滤波函数
(4) imageprocess.c           高光谱图像处理，格式转换bil2bsq。
(5) mathprocess.c            数学处理，求距离，夹角等。
(6) matrixprocess.c          矩阵处理，转至求逆，求特征值。
(7) morphology.c             形态学操作，开闭等
(8) pyramid.c                图像金字塔
(9) radiometriccalibration   遥感影像辐射矫正
(10)spectralprocess.c        光谱处理，光谱匹配等

3. gradient中是存放梯度算子
(1) canny                    canny算子
(2) laplacian                laplacian算子
(3) sobelprocess             sobel算子求边界

4. highgui中是图像显示模块

5. algorithm中是算法模块
(1) cem.c                    约束能量最小化目标检测
(2) cluster.c                聚类，光谱聚类，空间聚类
(3) dft.c                    离散傅里叶变换
(4) edgesignalenergy.c       边缘信号能量检测
(5) hisequalization.c        直方图
(6) houghlines.c             霍夫变换
(7) normalize.c              正则化
(8) otsuthreshold.c          大津阈值
(9) pca.c                    主成分分析
(10)shapematch.c             不变矩匹配


很多功能还在完善和测试中，欢迎各位从事遥感图像的同行提交 pull request。



mail 1) jimin@iscas.ac.cn  李济民




                                                           编者   李济民

			                                   2019/05/20 于 中国科学院软件研究所
