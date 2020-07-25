/*************************************************************************
	> File Name: modules/process/include/process/filter.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

/**
 * @brief      User-callable function to Filter a 2d mat.
 * @param[in]  src                 src mat .
 * @param[in]  dst                 out put mat .
 * @param[in]  kernel              filter kernel.
 * @param[in]  k_rows              row of kernel.
 * @param[in]  k_cols              col of kernel.
 * @param[in]  border_type         border type.
 **/
void hypercv_filter2D(simple_mat src, simple_mat dst, float* kernel, int k_rows, int k_cols, int border_type);

/**
 * @brief      User-callable function to medianblur.
 * @param[in]  src                 src mat .
 * @param[in]  dst                 out put mat .
 * @param[in]  size                median blur size.
 **/
void hypercv_medianblur(simple_mat src_mat, simple_mat dst_mat, int size);

/**
 * @brief      User-callable function to meanblur.
 * @param[in]  src                 src mat .
 * @param[in]  dst                 out put mat .
 * @param[in]  size                mean blur size.
 **/
void hypercv_meanblur(simple_mat src_mat, simple_mat dst_mat, int size);

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

/**
 * @brief      User-callable function to make a integral mat.
 * @param[in]  src                 src mat .
 * @param[in]  dst                 out put mat .
 **/
void hypercv_integral(simple_mat src, simple_mat dst);

/**
 * @brief      User-callable function to make a integral mat.
 * @param[in]  src                 src mat .
 * @param[in]  top                 add lines at top.
 * @param[in]  bottom              add lines at bottom.
 * @param[in]  left                add samples at left.
 * @param[in]  right               add samples at right.
 * @param[in]  border_type         border type.
 * @param[in]  value               if border_type == BORDER_CONSTANT.
 * retva       simple_mat.
 **/
simple_mat hypercv_copy_make_border(simple_mat src, int top, int bottom, int left, int right, int border_type, unsigned char value);
