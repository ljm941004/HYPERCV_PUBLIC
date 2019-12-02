/*************************************************************************
	> File Name: modules/process/include/process/filter.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

void hypercv_filter2D(simple_mat src, simple_mat dst, unsigned char* kernel, int k_rows, int k_cols, int border_type);

void hypercv_medianblur(simple_mat dst_mat, simple_mat src_mat, int size);

/**
 * @brief   User-callable function to create an unidimensional gaussian kernel.
 * @param[in]  kernel_size        lens of kernel.
 * @param[in]  sigma              Gaussian standard deviation.
 * @param[in]  ktype              type of kernel such as float.
 * retva       simple_mat.
 **/
simple_mat gaussian_kernel(int kernel_size, double sigma, int ktype);

/**
 * @brief      User-callable function to gaussian filter.
 * @param[in]  src_mat          input mat. 
 * @param[in]  ksize_width      length of X direction kernel.
 * @param[in]  ksize_height     length of Y direction kernel.
 * @param[in]  sigma1           Gaussian kernel standard deviation in X direction. 
 * @param[in]  sigma2           Gaussian kernel standard deviation in Y direction.
 * @param[in]  border_type      pixel extrapolation method
 * retva       simple_mat.
 **/
void hypercv_gaussian_blur(simple_mat src_mat, simple_mat dst_mat, int ksize_width, int ksize_height, double sigma1, double sigma2, int border_type);

/**
 * @brief      User-callable function to gaussian with kernel.
 * @param[in]  src_mat                input mat.
 * @param[in]  kernel_mat_x           gaussian kernel of X direction.
 * @param[in]  kernel_mat_y           gaussian kernel of Y direction. 
 * @param[in]  border_type            pixel extrapolation method.
 * retva       simple_mat.
 **/
void hypercv_gaussian_blur_with_kernel(simple_mat src_mat, simple_mat dst_mat, simple_mat kernel_mat_x, simple_mat kernel_mat_y, int border_type);

void hypercv_integral(simple_mat src, simple_mat dst);


simple_mat hypercv_copy_make_border(simple_mat src, int left, int right, int up, int down, int border_type);
