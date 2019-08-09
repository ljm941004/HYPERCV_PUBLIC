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


