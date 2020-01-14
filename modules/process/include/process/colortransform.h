/*************************************************************************
	> File Name: ../include/process/colortransform.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

/*
* @brief      change binary image 2 rgb image.
* @param[in]  binary_image       binary image.
* @retval     rgb image.
**/
simple_mat sm_binary2rgb(simple_mat binary_image);

/**
* @brief      change gray image 2 rgb image.
* @param[in]  gray_image       gray image.
* @retval     rgb image.
**/
simple_mat sm_gray2rgb(simple_mat gray_image);

/**
* @brief      change rgb image 2 gray image .
* @param[in]  rgb image.
* @retval     gray_image.
**/
simple_mat sm_rgb2gray(simple_mat rgb_image,int method);

/**
* @brief      change bgr image 2 rgb image .
* @param[in]  bgr image.
* @param[in]  rgb image.
**/
void sm_bgr2rgb(simple_mat src_mat, simple_mat dst_mat);
