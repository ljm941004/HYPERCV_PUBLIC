/*************************************************************************
	> File Name: process/include/process/threshold.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月09日 星期四 23时29分41秒
 ************************************************************************/

void hypercv_threshold_binary(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);

void hypercv_threshold_binary_inv(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);
void hypercv_threshold_trunc(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);
void hypercv_threshold_tozero(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);

void hypercv_threshold_tozero_inv(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);
void hypercv_threshold_mask(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);

void hypercv_threshold_otsu(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);
void hypercv_threshold_triangle(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value);

