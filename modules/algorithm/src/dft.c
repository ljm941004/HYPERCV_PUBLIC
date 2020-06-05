/*************************************************************************
	> File Name: algorithm/src/dft.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

int get_optimal_DFT_size(int size0)
{
    int a = 0, b = sizeof(optimal_DFT_sizetab)/sizeof(optimal_DFT_sizetab[0]) - 1;
    if( (unsigned)size0 >= (unsigned)optimal_DFT_sizetab[b] )
        return -1;

    while( a < b )
    {
        int c = (a + b) >> 1;
        if( size0 <= optimal_DFT_sizetab[c] )
            b = c;
        else
            a = c+1;
    }

    return optimal_DFT_sizetab[b];
}

void hypercv_dft(simple_mat src, simple_mat re_mat, simple_mat im_mat)
{
	hypercv_assert(src!=NULL&&re_mat!=NULL&&im_mat!=NULL,"INPUT MAT CANNOT BE NULL");
	hypercv_assert(src->rows == re_mat->rows&&src->rows == im_mat->rows&&src->cols == re_mat->cols&&src->cols == im_mat->cols,"src,im,re mat size equal");
	hypercv_assert(re_mat->data_type == 4&&im_mat->data_type == 4,"re_mat and im_mat data_type ==4");
	hypercv_assert(src->channels == re_mat->channels&&src->channels == im_mat->channels&&src->channels == 1,"only gray image");

	if(src->data_type == 1)
		hypercv_dft_uchar(src, re_mat, im_mat);
	else if (src->data_type == 12)
		hypercv_dft_ushort(src, re_mat, im_mat);

}

void hypercv_dft_uchar(simple_mat src, simple_mat re_mat, simple_mat im_mat)
{
	hypercv_assert(src!=NULL&&re_mat!=NULL&&im_mat!=NULL,"INPUT MAT CANNOT BE NULL");
	hypercv_assert(src->rows == re_mat->rows&&src->rows == im_mat->rows&&src->cols == re_mat->cols&&src->cols == im_mat->cols,"src,im,re mat size equal");
	hypercv_assert(re_mat->data_type == 4&&im_mat->data_type == 4,"re_mat and im_mat data_type ==4");
	hypercv_assert(src->channels == re_mat->channels&&src->channels == im_mat->channels&&src->channels == 1,"only gray image");

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

void hypercv_dft_ushort(simple_mat src, simple_mat re_mat, simple_mat im_mat)
{
	hypercv_assert(src!=NULL&&re_mat!=NULL&&im_mat!=NULL,"INPUT MAT CANNOT BE NULL");
	hypercv_assert(src->rows == re_mat->rows&&src->rows == im_mat->rows&&src->cols == re_mat->cols&&src->cols == im_mat->cols,"src,im,re mat size equal");
	hypercv_assert(re_mat->data_type == 4&&im_mat->data_type == 4,"re_mat and im_mat data_type ==4");
	hypercv_assert(src->channels == re_mat->channels&&src->channels == im_mat->channels&&src->channels == 1,"only gray image");

	float re,im,temp;

	int rows = src->rows;
	int cols = src->cols;
	unsigned short* src_data = (unsigned short*)src->data;
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

	hypercv_assert(src!=NULL, "INPUT MAT CAN NOT BE NULL");
	hypercv_assert(dst!=NULL, "OUTPUT MAT CAN NOT BE Null");

	hypercv_assert(src->rows == dst->rows&&src->cols == dst->cols,"SIZE ERROR");

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
	if(dst_mat->data_type == 1)
		hypercv_idft_uchar(re_mat, im_mat, dst_mat);
	else if(dst_mat->data_type == 12)
		hypercv_idft_ushort(re_mat, im_mat, dst_mat);
}

void hypercv_idft_uchar(simple_mat re_mat ,simple_mat im_mat, simple_mat dst_mat)
{
	hypercv_assert(re_mat->rows==im_mat->rows&&re_mat->rows==dst_mat->rows&&re_mat->cols == im_mat->cols&&re_mat->cols == dst_mat->cols,"INPUT MAT SIZE ERROR");
	hypercv_assert(re_mat->data_type == im_mat->data_type&&re_mat->data_type == 4,"re and im mat data_type == 4");
	hypercv_assert(dst_mat->data_type == 1,"output mat is gray image");

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

void hypercv_idft_ushort(simple_mat re_mat ,simple_mat im_mat, simple_mat dst_mat)
{
	hypercv_assert(re_mat->rows==im_mat->rows&&re_mat->rows==dst_mat->rows&&re_mat->cols == im_mat->cols&&re_mat->cols == dst_mat->cols,"INPUT MAT SIZE ERROR");
	hypercv_assert(re_mat->data_type == im_mat->data_type&&re_mat->data_type == 4,"re and im mat data_type == 4");
	hypercv_assert(dst_mat->data_type == 12,"output mat is gray image");

	int rows = re_mat->rows;
	int cols = re_mat->cols;
	float* re_data = (float*)re_mat->data;
	float* im_data = (float*)im_mat->data;
	unsigned short* dst_data = (unsigned short*)dst_mat->data;

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

void hypercv_magnitude(simple_mat re_mat, simple_mat im_mat, simple_mat dst_mat)
{
	hypercv_assert(re_mat->rows==im_mat->rows&&re_mat->rows==dst_mat->rows&&re_mat->cols == im_mat->cols&&re_mat->cols == dst_mat->cols,"INPUT MAT SIZE ERROR");
	hypercv_assert(re_mat->data_type == im_mat->data_type&&re_mat->data_type == 4,"re and im mat data_type == 4");
	hypercv_assert(dst_mat->data_type == 4,"output mat is float image");

	int cols = re_mat->cols;
	int rows = re_mat->rows;
	
	float* re_data = (float*)re_mat->data;
	float* im_data = (float*)im_mat->data;
	float* dst_data = (float*)dst_mat->data;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			dst_data[i*cols+j] = sqrt(pow(re_data[i*cols+j],2)+pow(im_data[i*cols*j],2));
		}
	}
}


