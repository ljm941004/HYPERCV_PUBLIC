/*************************************************************************
	> File Name: HisEqualization.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

/**            
 * @brief      function to hisequalization 
 * @param[in]  src_mat             input mat.        
 * @param[in]  dst_mat             result mat.
**/
void HisEqualization(simple_mat src_mat, simple_mat dst_mat);

/**            
 * @brief      function to  linear tension 
 * @param[in]  bsq_mat             input mat.        
 * @param[in]  dst_mat             result mat.
**/
void hyper_mat_linear_tension(hyper_mat bsq_mat, hyper_mat dst_mat);
