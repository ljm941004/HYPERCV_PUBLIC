/*************************************************************************
	> File Name: normalize.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

/**
 * @brief      User-callable function to normalize array or simplemat 
 * @param[in]  src        input array.
 * @param[in]  dst        output array.
 * @param[in]  alpha      alpha as float.
 * @param[in]  beta       beta as float.
 * @param[in]  norm_type  norm_type norm_inf=1 norm_l1=2 norm_l2=4 norm_minmax=32 .
 **/
void hypercv_normalize(simple_mat src, simple_mat dst, float alpha, float beta, int norm_type);
