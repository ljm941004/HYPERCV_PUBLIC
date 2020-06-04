/*************************************************************************
	> File Name: process/src/GeometricTransformation.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年02月02日 星期日 19时28分58秒
 ************************************************************************/
#include "precomp.h"

void simple_mat_flip_horizontal(simple_mat src_mat,simple_mat dst_mat)
{
	hypercv_assert(src_mat != NULL && dst_mat != NULL,"input mat cannot be null");
	
	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;
	hypercv_assert(rows == dst_mat->rows && cols == dst_mat->cols && channels == dst_mat->channels,"src_mat size != dst_mat size");

	unsigned char* src_data = (unsigned char*)src_mat->data;
	unsigned char* dst_data = (unsigned char*)dst_mat->data;

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<channels;k++)
			dst_data[i*cols*channels+j*channels+k] = src_data[i*cols*channels+(cols-1-j)*channels+k];
}


void simple_mat_flip_vertical(simple_mat src_mat,simple_mat dst_mat)
{
	hypercv_assert(src_mat != NULL && dst_mat != NULL,"input mat cannot be null");
	
	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;
	hypercv_assert(rows == dst_mat->rows && cols == dst_mat->cols && channels == dst_mat->channels,"src_mat size != dst_mat size");

	unsigned char* src_data = (unsigned char*)src_mat->data;
	unsigned char* dst_data = (unsigned char*)dst_mat->data;

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols*channels;j++)
				dst_data[i*cols*channels+j] = src_data[(rows-1-i)*cols*channels+j];
	
}

void simple_mat_flip(simple_mat src_mat, simple_mat dst_mat, int FLIPCODE)
{
	hypercv_assert(src_mat != NULL && dst_mat != NULL,"input mat cannot be null");
	
	int rows = src_mat->rows;
	int cols = src_mat->cols;
	hypercv_assert(rows == dst_mat->rows && cols == dst_mat->cols,"src_mat size != dst_mat size");
	
	switch(FLIPCODE)
	{
		
		case 1: 
			simple_mat_flip_horizontal(src_mat,dst_mat);
			break;
		case 0:
			simple_mat_flip_vertical(src_mat,dst_mat);
			break;
		case -1:
			{simple_mat temp = simple_mat_copy(src_mat);
			simple_mat_flip_horizontal(src_mat,temp);
			simple_mat_flip_vertical(temp,dst_mat);
			delete_simple_mat(temp);
			break;}
		default:	
			simple_mat_flip_horizontal(src_mat,dst_mat);
	}
}

void hypercv_pyramid_down(simple_mat src, simple_mat dst)
{
	hypercv_assert(src!=NULL,"input mat cannot be NULL");
	
	int src_rows = src->rows;
	int src_cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

	hypercv_assert(src_rows>=2&&src_cols>=2,"input mat size must > 2*2");
	hypercv_assert(dst != NULL, "dst mat == null");
	hypercv_assert(dst->rows ==(int)((src_rows+1)/2) && dst->cols==(int)((src_cols+1)/2),"dst size error");
	hypercv_assert(dst->data_type == src->data_type, "dst data_type error");
	
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
	hypercv_assert(src!=NULL,"input mat cannot be NULL");
	
	int src_rows = src->rows;
	int src_cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

	hypercv_assert(src_rows>=2&&src_cols>=2,"input mat size must > 2*2");
	hypercv_assert(dst != NULL, "dst mat == null");
	hypercv_assert(dst->rows == src_rows*2 && dst->cols== src_cols*2,"dst size error");
	hypercv_assert(dst->data_type == src->data_type, "dst data_type error");
	
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


hyper_mat hyper_mat_rotate(hyper_mat mat, double angle)
{

	if(cmpstr(mat->interleave,"bip")!=1)
		convert2bip(mat);
	double theta = angle * PI/180;
	double c = cos(theta);
	double s = sin(theta);

	int h = (mat->lines+1)/2;
	int w = (mat->samples+1)/2;

    float x0 = - w * c - h * s;
	float y0 = -h * c + w * s;
	float x1 = w * c - h * s;
	float y1 = -h * c - w * s;
	float x2 = w * c + h * s;
	float y2 = h * c - w * s;
	float x3 = -w * c + h * s;
	float y3 = h * c + w * s;
	float width1 = fabs(x2 - x0);
	float width2 = fabs(x3 - x1);
	float height1 = fabs(y2 - y0);
	float height2 = fabs(y3 - y1);

	int width = (width1 > width2 ? width1 : width2);
	int height = (height1 > height2 ? height1 : height2);

	hyper_mat dst_mat = create_hyper_mat_with_data(width, height, mat->bands,mat->data_type, mat->interleave, NULL, mat->wavelength);

	int di = x0 + width / 2;
	int dj = y0 + height / 2;
	
	unsigned char* src_data = (unsigned char*)mat->data;
	unsigned char* dst_data = (unsigned char*)dst_mat->data;
	
	int elem_size = get_elemsize(mat->data_type);

	for(int i=0;i<mat->lines;i++)
	{
		for(int j=0;j<mat->samples;j++)
		{
            int x = i * c + j * s + di;
			int y = j * c - i * s + dj;
			int dstOft = (x * width + y) * mat->bands * elem_size;
			int srcOft = (i * mat->samples + j) * mat->bands * elem_size;
			unsigned char* src = src_data + srcOft;
			unsigned char* dst = dst_data + dstOft;
			memcpy(dst,src,mat->bands*elem_size);
		}

	}
	return dst_mat;
}
