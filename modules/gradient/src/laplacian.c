/*************************************************************************
	> File Name: laplacian.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void hypercv_laplacian(simple_mat src, simple_mat dst, int k_size, int border_type)
{
	_assert(src!=NULL, "input mat can not be NULL");

	int cols = src->cols;
	int rows = src->rows;
	int channels = src->channels;
	int data_type = src->data_type;

	if(dst == NULL)
		dst = create_simple_mat(rows,cols,data_type,channels);

	float kernel[3][3] = {0.f,1.f,0.f,1.f,-4.f,1.f,0.f,1.f,0.f};

	if(k_size == 2)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				kernel[i][j] = kernel[i][j]*2;
	}

	int index_m,index_n;
	unsigned char* src_data = src->data;
	unsigned char* dst_data = dst->data;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			float sum = 0.0;
			for(int m=0;m<3;m++)
			{
				for(int n=0;n<3;n++)
				{
					if((i+m-1<0)||(i+m-1>=rows))
						index_m = hypercv_border_Interpolate(i+m-1,rows,border_type);
					else 	
						index_m = i+m-1;

					if(j+n-1<0||j+n>cols)
						index_n = hypercv_border_Interpolate(j+n-1,cols,border_type);
					else
						index_n = j+n-1;

					sum += kernel[m][n]*src_data[index_m*cols+index_n];
				}
			}
			dst_data[i*cols+j] = saturate_cast_float2uchar(sum);
		}
	}	
}
