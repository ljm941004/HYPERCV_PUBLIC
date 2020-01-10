/*************************************************************************
	> File Name: highgui/include/highgui/color.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/




void draw_POINT(simple_mat src_mat, simple_mat dst_mat, POINT* v, int point_num, RGB_data color, int size);

void draw_line(simple_mat src_mat, simple_mat dst_mat, POINT pt1, POINT pt2, RGB_data color, int thickness);
