/*************************************************************************
	> File Name: modules/process/src/hypercvresize.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年02月14日 星期五 09时43分23秒
 ************************************************************************/
#include "precomp.h"

void simple_mat_resize(simple_mat src_mat, simple_mat dst_mat, int flag)
{
    int src_datatype = src_mat -> data_type;
    int dst_datatype = dst_mat -> data_type;
    int src_rows = src_mat -> rows;
    int src_cols = src_mat -> cols;
    int dst_rows = dst_mat -> rows;
    int dst_cols = dst_mat -> cols;
    _assert(src_mat != NULL && dst_mat != NULL, "The source mat or the destination mat must not be null!");
    _assert(src_datatype == dst_datatype, "The source mat's type and the destination map's type must be the same!");



}
