/*************************************************************************
	> File Name: gradient.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月12日 星期日 22时58分04秒
 ************************************************************************/

/**            
 * @brief      sobel kernel to blur image.
 * @param[in]  src                 simple mat.        
 * @param[in]  dst                 dst mat.
 * @param[in]  threshold           threshold of blur.
 * @param[in]  border_type         type of border.
 **/
void hypercv_sobel(simple_mat src, simple_mat dst, int threshold, int border_type);

/**            
 * @brief      laplacian kernel to blur image.
 * @param[in]  src                 simple mat.        
 * @param[in]  dst                 dst mat.
 * @param[in]  k_size              laplacian kernel size.
 * @param[in]  border_type         type of border.
 **/
void hypercv_laplacian(simple_mat src, simple_mat dst, int k_size, int border_type);
