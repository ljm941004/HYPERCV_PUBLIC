//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_char(char *x,char *y,char*z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_uchar(unsigned char *x,unsigned char *y, unsigned char*z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_short(short *x,short *y,short*z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_ushort(unsigned short *x,unsigned short *y,unsigned short *z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_int(int *x,int *y,int*z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_uint(unsigned int *x, unsigned int *y, unsigned int *z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_float(float *x,float *y, float* z, int m,int k,int n);

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_double(double *x, double *y, double*z, int m,int k,int n);

//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_double(double *x,double *z, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_short(short *x,short*z, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_char(char *x, char *z, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_ushort(unsigned short *x, unsigned short*z, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_uchar(unsigned char *x,unsigned char*z, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void  TransMatrix_int(int *x,int *z , int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_float(float *x, float*z, int m, int n);
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_uint(unsigned int *x, unsigned int *z, int m, int n);

float matrix_norm_float(float* m,int size);

void matrix_QR_float(float* a, float* q, float *r,int m);

void cal_eigen_vector_float(float* a, float* eigenvector, float*eigenvalue,int m,int n);

void correlation_matrix_uchar(unsigned char* res, unsigned char* mat1, unsigned char* mat2, int l, int n, int m);

void correlation_matrix_char(char* res, char* mat1, char* mat2, int l, int n, int m);

void correlation_matrix_short(short* res, short* mat1, short* mat2, int l, int n, int m);

void correlation_matrix_ushort(unsigned short* res, unsigned short* mat1,unsigned short* mat2, int l, int n, int m);

void correlation_matrix_int(int* res, int* mat1, int* mat2, int l, int n, int m);

void correlation_matrix_uint(unsigned int* res,unsigned  int* mat1, unsigned int* mat2, int l, int n, int m);

void correlation_matrix_float(float* res, float* mat1, float* mat2, int l, int n, int m);





