/*************************************************************************
	> File Name: gradient.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月12日 星期日 22时56分11秒
 ************************************************************************/
#include "precomp.h"

void hypercv_laplacian(simple_mat src, simple_mat dst, int k_size, int border_type)
{
	_assert(src!=NULL&&dst!=NULL, "input mat can not be NULL");
	_assert(k_size>0,"kernel size > 0");
	int cols = src->cols;
	int rows = src->rows;
	int channels = src->channels;
	int data_type = src->data_type;

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


// default sobel ksize == 3 ,todo fix other ksize 

/**            
 * @brief      sobel kernel to blur image.
 * @param[in]  src                 simple mat.        
 * @param[in]  dst                 dst mat.
 * @param[in]  threshold           threshold of blur.
 * @param[in]  border_type         type of border.
 **/
void hypercv_sobel(simple_mat src, simple_mat dst, int threshold, int border_type)
{
	_assert(src->rows == dst->rows&&src->cols==dst->cols, "src size == dst size");
	_assert(border_type == BORDER_REFLECT
			||border_type == BORDER_REFLECT_101
			||border_type == BORDER_REPLICATE
			||border_type == BORDER_WRAP
			||border_type == BORDER_CONSTANT ,"Unknown/unsupported border type" );
	_assert(src->channels == 1,"sobel image channels == 1")

	int rows = src->rows;
	int cols = src->cols;

	int gradx = 0;
	int grady = 0;
	int pix;

	int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int gy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};

	int index_m,index_n;

	unsigned char* src_data = src->data;
	unsigned char* dst_data = dst->data;

	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			gradx = 0;
			grady = 0;

			for(int m=0; m<3; m++)
			{
				for(int n=0; n<3; n++)
				{
					if((i+m-1<0)||i+m-1>=rows)
						index_m = hypercv_border_Interpolate(i+m-1,rows,border_type);
					else
						index_m = i+m-1;
					if(j+n-1<0||j+n>cols)
						index_n = hypercv_border_Interpolate(j+n-1,cols,border_type);
					else
						index_n = j+n-1;

					gradx += gx[m][n]*src_data[index_m*cols+index_n];
					grady += gy[m][n]*src_data[index_m*cols+index_n];
				}
			}
        gradx = abs(gradx);
        grady = abs(grady);
		pix = gradx>grady?gradx:grady;
		dst_data[i*cols+j]=pix>threshold?255:0;
		}
	}
}
