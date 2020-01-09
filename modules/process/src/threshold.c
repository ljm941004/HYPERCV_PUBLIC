/*************************************************************************
	> File Name: threshold.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月09日 星期四 22时13分17秒
 ************************************************************************/
#include "precomp.h"


void hypercv_threshold_binary(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value)
{
	//todo
}


void hypercv_threshold_binary_inv(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value)
{}
void hypercv_threshold_trunc(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value){}
void hypercv_threshold_tozero(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value){}

void hypercv_threshold_tozero_inv(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value){}
void hypercv_threshold_mask(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value){}

void hypercv_threshold_otsu(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value){}
void hypercv_threshold_triangle(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value){}


void hypercv_threshold(simple_mat src_mat, simple_mat dst_mat, double thresh, double max_value, int type)
{
	_assert(src_mat!=NULL,"input mat cannot be NULL");
	_assert(dst_mat!=NULL,"output mat cannot be NULL");

	_assert(type == THRESH_BINARY ||
			type == THRESH_BINARY_INV||
			type == THRESH_TRUNC||
			type == THRESH_TOZERO||
			type == THRESH_TOZERO_INV||
			type == THRESH_MASK||
			type == THRESH_OTSU||
			type == THRESH_TRIANGLE , "threshold type error");

	switch(type)
	{
		case THRESH_BINARY:
			hypercv_threshold_binary(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_BINARY_INV:
			hypercv_threshold_binary_inv(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TRUNC:	
			hypercv_threshold_trunc(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TOZERO:
			hypercv_threshold_tozero(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TOZERO_INV:
			hypercv_threshold_tozero_inv(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_MASK:
			hypercv_threshold_mask(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_OTSU:
			hypercv_threshold_otsu(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TRIANGLE:
			hypercv_threshold_triangle(src_mat, dst_mat, thresh, max_value);
			break;


	}




}
