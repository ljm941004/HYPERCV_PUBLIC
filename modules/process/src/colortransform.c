/*************************************************************************
	> File Name: colortransform.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

#ifndef AVERAGE_METHOD 
#define AVERAGE_METHOD 0
#endif

#ifndef MAX_METHOD 
#define MAX_METHOD 1
#endif

#ifndef WEIGHTED_AVERAGE_METHOD 
#define WEIGHTED_AVERAGE_METHOD 2
#endif



/**
* @brief      change binary image 2 rgb image.
* @param[in]  binary_image       binary image.
* @retval     rgb image.
**/
simple_mat sm_binary2rgb(simple_mat binary_image)
{
	_assert(binary_image->channels == 1,"input binary_image channels == 1");

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

/**
* @brief      change gray image 2 rgb image.
* @param[in]  gray_image       gray image.
* @retval     rgb image.
**/
simple_mat sm_gray2rgb(simple_mat gray_image)
{	
	_assert(gray_image->channels == 1,"input gray image channels == 1");

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

/**
* @brief      change rgb image 2 gray image .
* @param[in]  rgb image.
* @retval     gray_image.
**/
simple_mat sm_rgb2gray(simple_mat rgb_image, int method)
{
	_assert(rgb_image->channels == 3,"input rgb_image channels == 3");

	int rows = rgb_image -> rows;
	int cols = rgb_image -> cols;
    
	simple_mat gray_image = create_simple_mat(rows,cols,1,1);

	unsigned char* gray_data = (unsigned char*)gray_image->data;
	unsigned char* rgb_data = (unsigned char*)rgb_image->data;

	float tmp=0;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			tmp=0.0;

			if (method == 1)
			{
				for(int k=0;k<3;k++)
					tmp = tmp>rgb_data[i*cols*3+j*3+k]?tmp:rgb_data[i*cols*3+j*3+k];

				gray_data[i*cols+j] = (int)tmp;
			}
			else if (method == 2)
			{
				tmp = rgb_data[i*cols*3+j*3]*0.299+rgb_data[i*cols*3+j*3+1]*0.578+rgb_data[i*cols*3+j*3+2]*0.114;
				gray_data[i*cols+j] = (int)tmp;
			}
			else
			{
				for(int k=0;k<3;k++)
					tmp+=rgb_data[i*cols*3+j*3+k];

				gray_data[i*cols+j] = (int)(tmp/3+0.5);
			}
		
		}
	}

	return gray_image;
}

