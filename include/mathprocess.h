/*************************************************************************
	> File Name: mathprocess.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
	> Created Time: 2019年06月30日 星期日 16时20分49秒
 ************************************************************************/



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
