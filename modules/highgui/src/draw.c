/*************************************************************************
	> File Name: highgui/src/draw.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void draw_POINT(simple_mat src_mat, simple_mat dst_mat, POINT* v, int point_num, RGB_data color, int size)
{
	_assert(src_mat!=NULL&&dst_mat !=NULL, "input mat cannot be NULL");
	_assert(src_mat->data_type == 1, "input mat data type == 1");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols == dst_mat->cols&&src_mat->channels==dst_mat->channels,"src,dst size should be equal");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;
	unsigned char* src_data = (unsigned char*)src_mat->data;
	unsigned char* dst_data = (unsigned char*)dst_mat->data;

	memcpy(dst_data,src_data,rows*cols*channels);

	for(int k=0;k<point_num;k++)
	{	
		int x = v[k].x;
		int y = v[k].y;
		for(int i=-size/2;i<=size/2;i++)
		{
			for(int j=-size/2;j<=size/2;j++)
			{
				if(x+i>=0&&x+i<cols&&y+j>=0&&y+j<rows)
				{
					if(channels == 3)
					{
						dst_data[(y+j)*cols*channels+(x+i)*channels] = color.b;	
						dst_data[(y+j)*cols*channels+(x+i)*channels+1] = color.g;
						dst_data[(y+j)*cols*channels+(x+i)*channels+2] = color.r;
					}
					else if(channels == 1)
						dst_data[(y+j)*cols+(x+i)] = color.r;	
				}
			}
		}
	}
}


void draw_line(simple_mat src_mat, simple_mat dst_mat, POINT pt1, POINT pt2, RGB_data color, int thickness)
{
	_assert(src_mat!=NULL&&dst_mat !=NULL, "input mat cannot be NULL");
	_assert(src_mat->data_type == 1, "input mat data type == 1");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols == dst_mat->cols&&src_mat->channels==dst_mat->channels,"src,dst size should be equal");

	int rows,cols;
	rows = src_mat->rows;
	cols = src_mat->cols;
	int channels = src_mat->channels;
	unsigned char* src_data = (unsigned char*)src_mat->data;
	unsigned char* dst_data = (unsigned char*)dst_mat->data;

	memcpy(dst_data,src_data,rows*cols*channels);	

	float k = (float)(pt2.x-pt1.x)/(pt2.y-pt1.y);
	float b = (float)pt1.y-k*pt1.x;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if(i==(int)(j*k+b+0.5))
			{
				for(int t=-thickness/2;t<=thickness/2;t++)
				{
					if(j+t>=0&&j+t<cols)
					{
						if(channels ==3)
						{
							dst_data[i*cols*channels+(j+t)*channels] = color.r;
							dst_data[i*cols*channels+(j+t)*channels+1] = color.g;
							dst_data[i*cols*channels+(j+t)*channels+2] = color.b;
						}
						else if(channels == 1)
							dst_data[i*cols+(j+t)] == color.r;
					}
				}
			}
		}
	}
}

