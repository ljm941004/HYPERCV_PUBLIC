/*************************************************************************
	> File Name: colortransform.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
simple_mat sm_binary2rgb(simple_mat binary_image)
{
	int rows = binary_image -> rows;
	int cols = binary_image -> cols;
	int channels = 3;
	simple_mat rgb_image = create_simple_mat(rows,cols,1,channels);

	unsigned char* binary_data = (unsigned char*)binary_image->data;
	unsigned char* rgb_data = (unsigned char*)rgb_image->data;
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<channels;k++)
				rgb_data[i*cols*3+j*3+k] = binary_data[i*cols+j]*255;

	return rgb_image;
}


simple_mat sm_gray2rgb(simple_mat gray_image)
{
	int rows = gray_image -> rows;
	int cols = gray_image -> cols;
	int channels = 3;
	simple_mat rgb_image = create_simple_mat(rows,cols,1,channels);

	unsigned char* gray_data = (unsigned char*)gray_image->data;
	unsigned char* rgb_data = (unsigned char*)rgb_image->data;
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<channels;k++)
				rgb_data[i*cols*3+j*3+k] = gray_data[i*cols+j];

	return rgb_image;
}

simple_mat sm_rgb2gray(simple_mat rgb_image)
{
	int rows = rgb_image -> rows;
	int cols = rgb_image -> cols;
    simple_mat gray_image = create_simple_mat(rows,cols,1,1);

	unsigned char* gray_data = (unsigned char*)gray_image->data;
	unsigned char* rgb_data = (unsigned char*)rgb_image->data;
	int tmp=0;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			tmp=0;
			for(int k=0;k<3;k++)
			{
				tmp+=rgb_data[i*cols*3+j*3+k];
			}
			tmp =(int)(tmp/3);

			gray_data[i*cols+j] = tmp;
		}
	}
	return gray_image;
}

