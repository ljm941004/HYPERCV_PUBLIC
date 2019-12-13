/*************************************************************************
	> File Name: mathprocess.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
	> Created Time: 2019年06月30日 星期日 16时18分43秒
 ************************************************************************/
#include "precomp.h"

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
double mean_double(double* t,int len)
{
	double res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_uint(unsigned int * t,int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_short(short *t, int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_ushort(unsigned short* t, int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_float(float* t, int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_uchar(unsigned char* t, int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_char(char* t, int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

/**
 * @brief      calculate the mean value . .
 * @param[in]  t          vector t
 * @param[in]  len        length of vector t
 **/
float mean_int(int *t, int len)
{
	float res=0;
	for(int i=0; i<len; i++)
		res+=t[i];
	res = res/len;
	return res;
}

void sort_array_down_float(float* a, int n)
{
	for(int i=0;i<n-1;++i)//n个数,总共需要进行n-1次
	{                 //n-1个数排完,第一个数一定已经归位
		//每次会将最大(升序)或最小(降序)放到最后面
		int f=1;//这里设置一个开关变量
		for(int j=0;j<n-i-1;++j)
		{
			if(a[j]<a[j+1])
			{
				float t;
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				f=0;
			}
		}
		if(1==f)//f为1说明没进行过冒泡,说明序列有序
			break;//若序列有序,则跳出排序即可
	}
}


long int hypercv_factorial( int n )
{
	if( n < 0 )
		return -1;

	if(n<=10)
		return hypercv_factorial_tab[n];

	long int m = 1;
	for(int i = 2 ; i <= n ; i++)
	{
		m *= i;
	}
	return m;
}
