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

float matrix_norm_float(float* m,int size)
{
	float ans = 0.0;
	for(int i=0;i<size;i++)
		ans+=m[i]*m[i];
	ans = (float)sqrt(ans);
	return ans;
}

void matrix_QR_float(float* a, float* q, float *r,int m)
{
	float* col_a = (float*)malloc(m*sizeof(float));
	float* col_q = (float*)malloc(m*sizeof(float));

	for (int j=0;j<m;j++)
	{
		for(int i=0;i<m;i++)
		{
			col_a[i] = a[i*m+j];
			col_q[i] = a[i*m+j];
		}
		for(int k=0;k<j;k++)
		{
			r[k*m+j] = 0;
			for(int i1=0; i1<m;i1++)
				r[k*m+j]+=col_a[i1];
			for(int i2=0;i2<m;i2++)
				col_q[i2] -= r[k*m+j];
		}

		float tmp = matrix_norm_float(col_q,m);
		r[j*m+j] = tmp;
		for(int i = 0;i<m;i++)
			q[i*m+j] = col_q[i]/tmp;
	}
}

void cal_eigen_vector_float(float* a, float* eigenvector, float*eigenvalue,int m,int n)
{
	float* temp = (float*)malloc(m*n*sizeof(float));
	float evalue ;
//todo fix bug
	for(int count =0;count < n;count++)
	{
		evalue = eigenvalue[count];
		memcpy(temp,a,m*n*sizeof(float));

		for(int i=0;i<m-1;i++)
		{
			float coe = temp[i*n+i];
			for(int j=1;j<n;j++)
				temp[i*n+j]/=coe;
			for (int i1 = i + 1; i1 < m; i1++)
			{
				coe = temp[i1 * n + i];
				for (int j1 = i; j1 < n; j1++)
				{
					temp[i1 * n + j1] -= coe * temp[i * n + j1];
				}
			}
		}

		float sum1 = eigenvector[(m-1)*n+count]=1;
		for(int i2=m-2;i2>=0;i2--)
		{
			float sum2 =0;
			for(int j2 =i2+1;j2<n;j2++)
				sum2 += temp[i2*n+j2]*eigenvector[j2*n+count];

			sum2 =-sum2/temp[i2*n+i2];
			sum1 += sum2*sum2;
			eigenvector[i2*n*count] = sum2;
		}
		sum1 = sqrt(sum1);
		for(int i=0;i<m;i++)
			eigenvector[i*n+count]/=sum1;
	}
	free(temp);
}

