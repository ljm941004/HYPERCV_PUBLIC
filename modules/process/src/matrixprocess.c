#include "precomp.h"


//矩阵乘法
/********参数表*******
@Parameter    x:    m行k列矩阵（用一维数组表示）
@Parameter    y:    k行n列矩阵（用一维数组表示）
@Parameter    m,k,n:    矩阵行列参数
@Parameter    z:    m行n列输出矩阵（用一维数组表示）
***********************/
char* MulMatrix_char(char *x,char *y, int m,int k,int n)
{
	char *z =(char*)malloc(m*n*sizeof(char));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

unsigned char* MulMatrix_uchar(char *x,char *y, int m,int k,int n)
{
	unsigned char *z =(unsigned char*)malloc(m*n*sizeof(unsigned char));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

short* MulMatrix_short(short *x,short *y, int m,int k,int n)
{
	short *z =(short*)malloc(m*n*sizeof(short));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

unsigned short * MulMatrix_ushort(unsigned short *x,unsigned short *y, int m,int k,int n)
{
	unsigned short *z =(unsigned short*)malloc(m*n*sizeof(unsigned short));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

int* MulMatrix_int(int *x,int *y, int m,int k,int n)
{
    int *z =( int*)malloc(m*n*sizeof(int));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

unsigned int * MulMatrix_uint(unsigned int *x, unsigned int *y, int m,int k,int n)
{
	unsigned int *z =(unsigned int *)malloc(m*n*sizeof(unsigned int));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

float* MulMatrix_float(float *x,float *y, int m,int k,int n)
{
    float *z =(float *)malloc(m*n*sizeof(float));
    for(int nm=0; nm<m; nm++)
        for(int nn=0; nn<n; nn++)
            for(int nk=0; nk<k; nk++)
                z[nm*n+nn] += x[nm*k+nk]*y[nk*n+nn];
}

double* MulMatrix_double(double *x, double *y, int m,int k,int n)
{
    double *z =(double*)malloc(m*n*sizeof(double));
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
double* TransMatrix_double(double *x, int m, int n)
{
	double*z = (double*)malloc(n*m*sizeof(double));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

short* TransMatrix_short(short *x, int m, int n)
{
	short* z = (short*)malloc(m*n*sizeof(short));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

char* TransMatrix_char(char *x, int m, int n)
{
	char* z = (char*)malloc(m*n*sizeof(char));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

unsigned short* TransMatrix_ushort(unsigned short *x, int m, int n)
{
	unsigned short* z = (unsigned short*)malloc(m*n*sizeof(unsigned short));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

unsigned char* TransMatrix_uchar(unsigned char *x, int m, int n)
{
	unsigned char* z = (unsigned char*)malloc(m*n*sizeof(unsigned char));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

int* TransMatrix_int(int *x, int m, int n)
{
	int* z = (int*)malloc(m*n*sizeof(int));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

float* TransMatrix_float(float *x, int m, int n)
{
	float* z = (float*)malloc(m*n*sizeof(float));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}

unsigned int* TransMatrix_uint(unsigned int *x, int m, int n)
{
	unsigned int* z = (unsigned int*)malloc(m*n*sizeof(unsigned int));
    for(int nm=0; nm<m; nm++)            //对原矩阵第nm行
        for(int nn=0; nn<n; nn++)        //对原矩阵第nn列
            z[nn*m+nm] = x[nm*n+nn];    //z矩阵第nn行第nm列
}


