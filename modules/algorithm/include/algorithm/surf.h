/*************************************************************************
	> File Name: algorithm/include/algorithm/surf.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

void calc_feature_point_descriptor(simple_mat integral_mat,FPVector *fps, size_t start_index, size_t end_index);

void calc_orientation(simple_mat integral_mat, feature_point f);
void calc_descriptor(simple_mat integral_mat, feature_point f);
float calculateAngle(const float x, const float y);
