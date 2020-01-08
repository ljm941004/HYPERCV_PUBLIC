/*************************************************************************
	> File Name: highgui/src/draw.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"



void draw_POINT(simple_mat mat , POINT* v,RGB_data color, int size)
{
	_assert( mat!=NULL, "input mat cannot be NULL");
	_assert(mat->data_type == 1, "input mat data type == 1");
	simple_mat rgb_mat;
	if(mat->channels == 1)
		rgb_mat = sm_gray2rgb(mat);
	else
		rgb_mat = mat;

	int rows = mat->rows;
	int cols = mat->cols;
	int channels = rgb_mat->channels;

	unsigned char* data = (unsigned char*)rgb_mat->data;

	POINT* iter = v;

    for(int k=0;k<vector_size(v);k++)
	{
		
		int x = iter->x;
		int y = iter->y;
		for(int i=-size/2;i<=size/2;i++)
		{
			for(int j=-size/2;j<=size/2;j++)
			{
				if(x+i>=0&&x+i<cols&&y+j>=0&&y+j<rows)
				{
					data[(y+j)*cols*channels+(x+i)*channels] = color.b;	
					data[(y+j)*cols*channels+(x+i)*channels+1] = color.g;
					data[(y+j)*cols*channels+(x+i)*channels+2] = color.r;
				}
			}

		}
		iter++;
	}

}

