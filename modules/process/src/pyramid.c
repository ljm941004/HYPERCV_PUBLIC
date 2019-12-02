/*************************************************************************
	> File Name: process/src/pyramid.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void hypercv_pyramid_up(simple_mat src, simple_mat dst)
{
	_assert(src!=NULL,"input mat cannot be NULL");
	int src_rows = src->rows;
	int src_cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

	_assert(src_rows>=2&&src_cols>=2,"input mat size must > 2*2");

	_assert(dst != NULL, "dst mat == null");

	_assert(dst->rows ==(int)((src_rows+1)/2) && dst->cols==(int)((src_cols+1)/2),"dst size error");
	_assert(dst->data_type == src->data_type, "dst data_type error");

	simple_mat src_mat ;
	if(src_cols%2==1)
		src_mat = hypercv_copy_make_border(src,0,1,0,0,1);
	else
		src_mat = src;
	
	int dst_rows = dst->rows;
	int dst_cols = dst->cols;

	unsigned char* src_data = (unsigned char*) src_mat->data;
	unsigned char* dst_data = (unsigned char*) dst->data;

	for(int i=0;i<dst_rows;i++)
		for(int j=0;j<dst_cols;j++)
			for(int m=0;m<channels;m++)
			  dst_data[i*dst_cols*channels+j*channels+m] = src_data[2*i*src_mat->cols*channels+2*j*channels+m];
	


	//	hypercv_gaussian_blur(,dst,5,5,0,0,1);
}


