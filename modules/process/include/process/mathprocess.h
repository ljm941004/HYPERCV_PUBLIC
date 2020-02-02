/*************************************************************************
	> File Name: mathprocess.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
	> Created Time: 2019年06月30日 星期日 16时20分49秒
 ************************************************************************/

////////////////////////////


///////////////////////////

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
double mean_double(double* t,int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_uint(unsigned int * t,int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_short(short *t, int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_ushort(unsigned short* t, int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_float(float* t, int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_uchar(unsigned char* t, int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_char(char* t, int len);

/**
* @brief      calculate the mean value . .
* @param[in]  t          vector t
* @param[in]  len        length of vector t
**/
float mean_int(int *t, int len);

void sort_array_down_float(float* a, int n);

//
/**
* @brief      calculate the mean value of vector x. 
* @param[in]  type        template data type.
* @param[in]  x           vector x.
* @param[in]  len         length of vector x.
**/
/*
	
template <class type>
float mean(type* x, int len)
{
	float res = 0;
	for(int i=0; i<len; i++)
		res = res +(float)x[i];
	res = res/len;
	return res;
}
*/
/**
* @brief      calculate the variance value of vector x. 
* @param[in]  type        template data type.
* @param[in]  x           vector x.
* @param[in]  len         length of vector x.
**/
/*
template <class type>
float variance(type* x, int len)
{
	float res = 0;
	float m = mean<type>(x,len);
	for(int i=0; i<len; i++)
		res = res +(float)((x[i]-m)*(x[i]-m));
	res = res/len;
	return res;
}
*/
/**
* @brief      calculate the covariance value of vector x. 
* @param[in]  type        template data type.
* @param[in]  x           vector x.
* @param[in]  y           vector y.
* @param[in]  len         length of vector x.
**/
/*
 *
template <class type1,class type2>
float covariance(type1* x, type2* y, int len)
{
	float res = 0;
	float mx = mean<type1>(x,len);
	float my = mean<type2>(y,len);
	for(int i=0; i<len; i++)
		res += (x[i]-mx)(y[i]-my);
	return res/len;
}

*/
