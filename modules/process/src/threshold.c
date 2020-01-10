/*************************************************************************
	> File Name: threshold.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月09日 星期四 22时13分17秒
 ************************************************************************/
#include "precomp.h"

void hypercv_threshold_binary(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
	_assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]>thresh)
			dst_data[i] = max_value;
		else
			dst_data[i] = 0;
	}
}

void hypercv_threshold_binary_inv(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]<=thresh)
			dst_data[i] = max_value;
		else
			dst_data[i] = 0;
	}
}

void hypercv_threshold_trunc(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]>thresh)
			dst_data[i] = thresh;
		else
			dst_data[i] = src_data[i];
	}
}

void hypercv_threshold_tozero(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]>thresh)
			dst_data[i] = src_data[i];
		else
			dst_data[i] = 0;
	}
}

void hypercv_threshold_tozero_inv(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]<=thresh)
			dst_data[i] = src_data[i];
		else
			dst_data[i] = 0;
	}	
}

void hypercv_threshold_mask(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value){}

void hypercv_threshold_otsu(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value){}

void hypercv_threshold_triangle(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value){}

void hypercv_threshold(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value, int type)
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
