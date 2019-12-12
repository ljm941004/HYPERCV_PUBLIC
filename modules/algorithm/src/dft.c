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
