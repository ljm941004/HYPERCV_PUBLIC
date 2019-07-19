/*************************************************************************
	> File Name: morphology.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
//only data_type unsigned char 
simple_mat corrosion_2d(simple_mat mat, S_2D s)
{
	int rows = mat->rows;
	int cols = mat->cols;
	int channels = mat->channels;
	int data_type = mat->data_type;
	int elemsize = get_elemsize(mat->data_type);
	
	int width = s->width;
	int height = s->height;

	if (cols < width || rows < height)
	{
		printf("wrong, mat's size small than 2d struct");
		return mat;
	}	
	
	simple_mat dst_mat = create_simple_mat(rows, cols, data_type, channels);

	unsigned char * src = (unsigned char*)mat->data;
	unsigned char * dst = (unsigned char*)dst_mat->data;
	unsigned char * sd = (unsigned char*) s->data;

	int flag = 0;
	for(int i=(int)(height/2); i<rows-(int)(height/2); i++)
	{
		for(int j=(int)(width/2); j<cols-(int)(width/2); j++)
		{
			if(src[i*rows+j]!=0)
			{

//todo


			
			
			
			}
		
		
		
		}
	
	
	
	
	}
	








}




