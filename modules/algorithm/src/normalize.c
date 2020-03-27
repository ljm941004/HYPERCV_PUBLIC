/*************************************************************************
	> File Name: normalize.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

/**
 * @brief      User-callable function to normalize array or simplemat 
 * @param[in]  src        input array.
 * @param[in]  dst        output array.
 * @param[in]  alpha      alpha as float.
 * @param[in]  beta       beta as float.
 * @param[in]  norm_type  norm_type norm_inf=1 norm_l1=2 norm_l2=4 norm_minmax=32 .
 **/

void hypercv_normalize(simple_mat src, simple_mat dst, float alpha, float beta, int norm_type)
{
    _assert(src!=NULL&&dst!=NULL,"INPUT MAT could not be null");
	_assert(dst->rows==src->rows&&dst->cols==src->cols,"src size == dst size");

	if(src->data_type == 1)
		hypercv_normalize_uchar(src, dst, alpha, beta, norm_type);
	else if(src->data_type == 4) 
		hypercv_normalize_float(src, dst, alpha, beta, norm_type);
}

void hypercv_normalize_uchar(simple_mat src, simple_mat dst, float alpha, float beta, int norm_type)
{
	_assert(src!=NULL&&dst!=NULL,"INPUT MAT could not be null");
	_assert(dst->rows==src->rows&&dst->cols==src->cols,"src size == dst size");
	int rows = src->rows;
	int cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

//only uchar//todo 
    unsigned char* src_data = (unsigned char*)src->data;
	unsigned char* dst_data = (unsigned char*)dst->data;

	if(norm_type == NORM_L1)
	{
		float L1_norm = 0;
		for (int i =0;i< rows*cols;i++ )
			L1_norm += src_data[i]>=0?src_data[i]:(-src_data[i]);
		for(int i=0;i<rows*cols;i++)
			dst_data[i] =saturate_cast_float2uchar(src_data[i]*alpha/L1_norm);
	}
	if(norm_type == NORM_L2)
	{
		float L2_norm = 0;
		for (int i =0;i< rows*cols;i++ )
			L2_norm += src_data[i]*src_data[i];
		for(int i=0;i<rows*cols;i++)
			dst_data[i] = saturate_cast_float2uchar(src_data[i]*alpha/sqrt(L2_norm));
	}

	if(norm_type == NORM_INF)
	{
		float INF_norm = 0;
		for (int i =0;i< rows*cols;i++ )
			INF_norm = src_data[i]>INF_norm?src_data[i]:INF_norm;
		for(int i=0;i<rows*cols;i++)
			dst_data[i] = saturate_cast_float2uchar(src_data[i]*alpha/INF_norm);
	}
	if(norm_type == NORM_MINMAX)
	{
		float maxsrc=-1000000,minsrc=1000000;
		for(int i=0;i<rows*cols;i++)
		{
			maxsrc = maxsrc>src_data[i]?maxsrc:src_data[i];
			minsrc = minsrc<src_data[i]?minsrc:src_data[i];
		}
		float b = alpha>beta?alpha:beta;
		float a = alpha>beta?beta:alpha;

		for(int i=0;i<rows*cols;i++)
			dst_data[i] = saturate_cast_float2uchar((src_data[i]-minsrc)*(b-a)/(maxsrc-minsrc)+a);
	}
}

 
void hypercv_normalize_float(simple_mat src, simple_mat dst, float alpha, float beta, int norm_type)
{
	_assert(src!=NULL&&dst!=NULL,"INPUT MAT could not be null");
	_assert(dst->rows==src->rows&&dst->cols==src->cols,"src size == dst size");
	int rows = src->rows;
	int cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

//only uchar//todo 
    float* src_data = (float*)src->data;
	float* dst_data = (float*)dst->data;

	if(norm_type == NORM_L1)
	{
		float L1_norm = 0;
		for (int i =0;i< rows*cols;i++ )
			L1_norm += src_data[i]>=0?src_data[i]:(-src_data[i]);
		for(int i=0;i<rows*cols;i++)
			dst_data[i] =saturate_cast_float2uchar(src_data[i]*alpha/L1_norm);
	}
	if(norm_type == NORM_L2)
	{
		float L2_norm = 0;
		for (int i =0;i< rows*cols;i++ )
			L2_norm += src_data[i]*src_data[i];
		for(int i=0;i<rows*cols;i++)
			dst_data[i] = saturate_cast_float2uchar(src_data[i]*alpha/sqrt(L2_norm));
	}

	if(norm_type == NORM_INF)
	{
		float INF_norm = 0;
		for (int i =0;i< rows*cols;i++ )
			INF_norm = src_data[i]>INF_norm?src_data[i]:INF_norm;
		for(int i=0;i<rows*cols;i++)
			dst_data[i] = saturate_cast_float2uchar(src_data[i]*alpha/INF_norm);
	}
	if(norm_type == NORM_MINMAX)
	{
		float maxsrc=-1000000,minsrc=1000000;
		for(int i=0;i<rows*cols;i++)
		{
			maxsrc = maxsrc>src_data[i]?maxsrc:src_data[i];
			minsrc = minsrc<src_data[i]?minsrc:src_data[i];
		}
		float b = alpha>beta?alpha:beta;
		float a = alpha>beta?beta:alpha;

		for(int i=0;i<rows*cols;i++)
			dst_data[i] = saturate_cast_float2uchar((src_data[i]-minsrc)*(b-a)/(maxsrc-minsrc)+a);
	}
}


