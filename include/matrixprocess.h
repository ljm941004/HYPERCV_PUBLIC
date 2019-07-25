//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
char* MulMatrix_char(char *x,char *y, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
short* MulMatrix_short(short *x,short *y, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
unsigned short * MulMatrix_ushort(unsigned short *x,unsigned short *y, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
int* MulMatrix_int(int *x,int *y, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
unsigned int * MulMatrix_uint(unsigned int *x, unsigned int *y, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
float* MulMatrix_float(float *x,float *y, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
double* MulMatrix_double(double *x, double *y, int m,int k,int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
double* TransMatrix_double(double *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
short* TransMatrix_short(short *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
char* TransMatrix_char(char *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
unsigned short* TransMatrix_ushort(unsigned short *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
unsigned char* TransMatrix_uchar(unsigned char *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
int* TransMatrix_int(int *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
float* TransMatrix_float(float *x, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
unsigned int* TransMatrix_uint(unsigned int *x, int m, int n);
