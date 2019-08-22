#include "precomp.h"


//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_char(char *x,char *y,char*z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}
//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_uchar(unsigned char *x,unsigned char *y, unsigned char*z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}
//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_short(short *x,short *y,short*z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}
//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_ushort(unsigned short *x,unsigned short *y,unsigned short *z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_int(int *x,int *y,int*z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}
//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_uint(unsigned int *x, unsigned int *y, unsigned int *z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}
//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_float(float *x,float *y, float* z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}
//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
void MulMatrix_double(double *x, double *y, double*z, int m,int k,int n)
{
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_double(double *x,double *z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_short(short *x,short*z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_char(char *x, char *z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_ushort(unsigned short *x, unsigned short*z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_uchar(unsigned char *x,unsigned char*z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void  TransMatrix_int(int *x,int *z , int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_float(float *x, float*z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}
//距阵转置
/********参数表*******
@Parameter    x:    m行n列矩阵（用一维数组表示）
@Parameter    m,n:    矩阵行列数
@Parameter    z:    n行m列矩阵（用一维数组表示）
***********************/
void TransMatrix_uint(unsigned int *x, unsigned int *z, int m, int n)
{
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}


