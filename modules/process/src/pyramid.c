/*************************************************************************
	> File Name: process/src/pyramid.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void hypercv_pyramid_down(simple_mat src, simple_mat dst)
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
	
	simple_mat tmp = create_simple_mat(src_rows,src_cols,data_type,channels);

	hypercv_gaussian_blur(src,tmp,5,5,0,0,1);

	int dst_rows = dst->rows;
	int dst_cols = dst->cols;

	unsigned char* dst_data = (unsigned char*) dst->data;
	unsigned char* tmp_data = (unsigned char*) tmp->data;

	for(int i=0;i<dst_rows;i++)
		for(int j=0;j<dst_cols;j++)
			for(int m=0;m<channels;m++)
			  dst_data[i*dst_cols*channels+j*channels+m] = tmp_data[2*i*src->cols*channels+2*j*channels+m];
	
}

void hypercv_pyramid_up(simple_mat src, simple_mat dst)
{
	_assert(src!=NULL,"input mat cannot be NULL");
	
	int src_rows = src->rows;
	int src_cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

	_assert(src_rows>=2&&src_cols>=2,"input mat size must > 2*2");
	_assert(dst != NULL, "dst mat == null");
	_assert(dst->rows == src_rows*2 && dst->cols== src_cols*2,"dst size error");
	_assert(dst->data_type == src->data_type, "dst data_type error");
	
	simple_mat tmp = simple_mat_copy(dst);

	int dst_rows = dst->rows;
	int dst_cols = dst->cols;

	unsigned char* src_data = (unsigned char*) src->data;
	unsigned char* tmp_data = (unsigned char*) tmp->data;

	for(int i=0;i<dst_rows;i++)
	{
		for(int j=0;j<dst_cols;j++)
		{
			if(i%2 == 1||j%2 == 1)
			{
				for(int m=0;m<channels;m++)
					tmp_data[i*dst_cols*channels+j*channels+m] = 0;
			}
			else
			{
				for(int m=0;m<channels;m++)
					tmp_data[i*dst_cols*channels+j*channels+m] = src_data[i/2*src->cols*channels+j/2*channels+m];
			}
		}
	}

	simple_mat kernel = gaussian_kernel(5,0,4);

	float* kernel_data = (float*)kernel->data;
	for(int i=0;i<5;i++)
		kernel_data[i]=kernel_data[i]*2;

	hypercv_gaussian_blur_with_kernel(tmp,dst,kernel,kernel,1);
}

