/*************************************************************************
	> File Name: sobel.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

/**            
 * @brief      sobel kernel to blur image.
 * @param[in]  src                 simple mat.        
 * @param[in]  dst                 dst mat.
 * @param[in]  threshold           threshold of blur.
 * @param[in]  border_type         type of border.
 **/
void hypercv_sobel(simple_mat src, simple_mat dst, int threshold, int border_type);
