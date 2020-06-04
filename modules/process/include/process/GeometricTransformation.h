/*************************************************************************
	> File Name: process/include/process/GeometricTransformation.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年02月02日 星期日 19时30分10秒
 ************************************************************************/

void simple_mat_flip_horizontal(simple_mat src_mat,simple_mat dst_mat);
void simple_mat_flip_vertical(simple_mat src_mat,simple_mat dst_mat);
void simple_mat_flip(simple_mat src_mat, simple_mat dst_mat, int FLIPCODE);
void hypercv_pyramid_down(simple_mat src, simple_mat dst);

void hypercv_pyramid_up(simple_mat src, simple_mat dst);


hyper_mat hyper_mat_rotate(hyper_mat mat, double angle);
