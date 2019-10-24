/*************************************************************************
	> File Name: HisEqualization.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

/**            
 * @brief      function to hisequalization 
 * @param[in]  src_mat             input mat.        
 * @param[in]  dst_mat             result mat.
**/
void HisEqualization(simple_mat dst_mat, simple_mat src_mat)
{
	_assert(src_mat!=NULL&&dst_mat!=NULL,"input mat could not be NULL");
	
	int rows = src_mat->rows;
	int cols = src_mat->cols;
	_assert(rows==dst_mat->rows&&dst_mat->cols==cols,"input mat size equal");

	unsigned char* data = (unsigned char*) src_mat ->data;
	unsigned char* dst_data = (unsigned char*) dst_mat ->data;

	int hist[256] = {0};
	
	for(int i=0; i<rows*cols; i++)
		hist[data[i]]+=1;
	
	for(int i=1; i<256; i++)
	{
		hist[i] += hist[i-1];
		hist[i] = hist[i]*255/(rows*cols);
	}
	
	for(int i=0; i<rows*cols; i++)
		dst_data[i] = hist[data[i]];
}

void hyper_mat_linear_tension(hyper_mat dst_mat, hyper_mat bsq_mat)
{
	_assert(cmpstr(bsq_mat->interleave,"bsq")==1,"input src mat must be bsq");
	int samples = bsq_mat -> samples;
	int lines = bsq_mat -> lines;
	int bands = bsq_mat -> bands;
	_assert(dst_mat->samples == samples&& dst_mat->lines == lines&&dst_mat->bands == bands,"src mat size == dst mat size");
	_assert(dst_mat ->data_type ==1,"dst data type char");
	float * srcdata = (float*)bsq_mat -> data;
	unsigned char* dstdata = (unsigned char*) dst_mat->data;
	float maxdata = 0.0;
	float mindata = 1000000;
	float tmp = 0.0;
	//todo fix only float
	int res=0;
	for(int k=0; k<bands; k++)
	{
		maxdata = 0.0;
		mindata = 1000000000;
		tmp =0.0;
		res =0;
		for(int i=0; i<lines;i++)
		{
			for(int j=0; j<samples; j++)
			{
				tmp = srcdata[k*samples*lines+i*samples+j];
				if (maxdata<tmp)
				    maxdata = tmp;
				if(mindata>tmp)
					mindata = tmp;
			}
		}
		float m = 255/(maxdata-mindata);
		float n = -mindata*255/(maxdata-mindata);
		for(int i=0; i<lines;i++)
		{
			for(int j=0; j<samples; j++)
			{
				tmp = srcdata[k*samples*lines+i*samples+j];
				res = (int)(tmp*m+n);
				if(res<=0)
				{
					if (tmp==0)
						dstdata[k*samples*lines+i*samples+j]=0;
					else
						dstdata[k*samples*lines+i*samples+j]=1;
				}
				else if(res>=255)
						dstdata[k*samples*lines+i*samples+j]=255;
				else
						dstdata[k*samples*lines+i*samples+j]=res;
			}
		}
	}
}
