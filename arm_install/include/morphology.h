/*************************************************************************
	> File Name: morphology.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

/**
* @brief      simple_mat corrosion with 2D struct.
* @param[in]  simple_mat    2d image mat.
* @param[in]  S_2D          2D struct.
* @retval     simple_mat    2d image mat.
**/
void hypercv_corrosion(simple_mat mat, simple_mat dst_mat, S_2D s);

/**
* @brief      simple_mat expend with 2D struct.
* @param[in]  simple_mat    2d image mat.
* @param[in]  S_2D          2D struct.
* @retval     simple_mat    2d image mat.
**/
void hypercv_expend(simple_mat mat, simple_mat dst_mat, S_2D s);

void hypercv_open(simple_mat src, simple_mat dst, S_2D kernel, int iterations);
void hypercv_close(simple_mat src, simple_mat dst, S_2D kernel, int iterations);
