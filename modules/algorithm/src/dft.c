/*************************************************************************
	> File Name: algorithm/src/dft.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

int getOptimalDFTSize( int size0 )
{
    int a = 0, b = sizeof(optimalDFTSizeTab)/sizeof(optimalDFTSizeTab[0]) - 1;
    if( (unsigned)size0 >= (unsigned)optimalDFTSizeTab[b] )
        return -1;

    while( a < b )
    {
        int c = (a + b) >> 1;
        if( size0 <= optimalDFTSizeTab[c] )
            b = c;
        else
            a = c+1;
    }

    return optimalDFTSizeTab[b];
}

void hypercv_dft(simple_mat src, simple_mat re_mat, simple_mat im_mat)
{
	_assert(src!=NULL&&re_mat!=NULL&&im_mat!=NULL,"INPUT MAT CANNOT BE NULL");
	_assert(src->rows == re_mat->rows&&src->rows == im_mat->rows&&src->cols == re_mat->cols&&src->cols == im_mat->cols,"src,im,re mat size equal");
	_assert(re_mat->data_type == 4&&im_mat->data_type == 4,"re_mat and im_mat data_type ==4");
	_assert(src->channels == re_mat->channels&&src->channels == im_mat->channels&&src->channels == 1,"only gray image");
	float re,im,temp;

	int rows = src->rows;
	int cols = src->cols;
	unsigned char* src_data = (unsigned char*)src->data;
	float* im_data = (float*)im_mat->data;
	float* re_data = (float*)re_mat->data;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			re = 0.0;
			im = 0.0;

			for(int x=0;x<rows;x++)
			{
				for(int y=0;y<cols;y++)
				{
					temp = (float)i*x/(float)rows + (float)j*y/(float)cols;
					re += src_data[x*cols+y]*cos(-2*PI*temp);
					im += src_data[x*cols+y]*sin(-2*PI*temp);
				}
			}

			re_data[i*cols+j] = re;
			im_data[i*cols+j] = im;
		}
	}

}

void hypercv_dft_frespectrum(simple_mat src, simple_mat dst)
{

	_assert(src!=NULL, "INPUT MAT CAN NOT BE NULL");
	_assert(dst!=NULL, "OUTPUT MAT CAN NOT BE Null");

	_assert(src->rows == dst->rows&&src->cols == dst->cols,"SIZE ERROR");

	int rows = src->rows;
	int cols = src->cols;

	unsigned char* src_data = (unsigned char*)src->data;
	unsigned char* dst_data = (unsigned char*)dst->data;

	float re, im, temp;
	int move;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			re = 0.0;
			im = 0.0;

			for(int x=0;x<rows;x++)
			{
				for(int y=0;y<cols;y++)
				{
					temp = (float)i*x/(float)rows+(float)j*y/(float)cols;
					move = (x+y)%2 == 0?1:-1;
					re += src_data[x*cols+y]*cos(-2*PI*temp)*move;
					im += src_data[x*cols+y]*sin(-2*PI*temp)*move;

				}

			}
			
			dst_data[i*cols+j] = saturate_cast_float2uchar(sqrt(re*re+im*im)/sqrt(rows*cols));
			
		}
	}
}


void hypercv_idft(simple_mat re_mat ,simple_mat im_mat, simple_mat dst_mat)
{
	_assert(re_mat->rows==im_mat->rows&&re_mat->rows==dst_mat->rows&&re_mat->cols == im_mat->cols&&re_mat->cols == dst_mat->cols,"INPUT MAT SIZE ERROR");
	_assert(re_mat->data_type == im_mat->data_type&&re_mat->data_type == 4,"re and im mat data_type == 4");
	_assert(dst_mat->data_type == 1,"output mat is gray image");

	int rows = re_mat->rows;
	int cols = re_mat->cols;
	float* re_data = (float*)re_mat->data;
	float* im_data = (float*)im_mat->data;
	unsigned char* dst_data = (unsigned char*)dst_mat->data;

	float real,temp;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			real = 0;
			for (int x = 0; x < rows; x++)
			{
				for (int y = 0; y < cols; y++)
				{
					temp = (float)i * x / (float)rows+ (float)j * y / (float)cols;

					real += re_data[x*cols+y]*cos(2 * PI * temp) -im_data[x*cols+y] * sin(2 * PI * temp);
				}
			}

			dst_data[i*cols+j] =saturate_cast_float2uchar(real / sqrt(rows*cols));
		}
	}
}

