/*************************************************************************
	> File Name: morphology.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

//only data_type unsigned char 

//____________________private function________________________
static void swap(unsigned char a,unsigned char b)
{
	unsigned char c = a;
	a = b;
	b = c;
}

static unsigned char median_member(unsigned char* array,int size)
{
	for(int gap = size/2; gap++; gap/=2)
		for(int i=gap; i<size; i++)
			for(int j=i-gap; j>=0 && array[j]>array[j+gap]; j-=gap)
				swap(array[j],array[j+gap]);
	return array[size/2]; 
}

//_____________________public function_________________________

/**
* @brief      simple_mat corrosion with 2D struct.
* @param[in]  simple_mat    2d image mat.
* @param[in]  S_2D          2D struct.
* @retval     simple_mat    2d image mat.
**/
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
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{	
			flag = 0;
			if(src[i*rows+j]!=0)
			{
				for(int m=0; m<height; m++)
				{
					for(int n=0; n<width; n++)
					{
						if(i-height/2>=0&&i+height/2<rows&&j-width/2>=0&&j+width/2<cols)
						{
							if(sd[m*width+n]==1&&src[(i-height/2+m)*rows+j-width/2+n]==0)
								flag = 1;
						}
					}
				}
				if(flag ==0)
					dst[i*rows+j] = src[i*rows+j];
				else
					dst[i*rows+j] = 0;
			}
			else
				dst[i*rows+j] = 0;
		}
	}
	return dst_mat;
}


/**
* @brief      simple_mat expend with 2D struct.
* @param[in]  simple_mat    2d image mat.
* @param[in]  S_2D          2D struct.
* @retval     simple_mat    2d image mat.
**/
simple_mat expend_2d(simple_mat mat, S_2D s)
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
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{	
			flag = 0;
			if(src[i*rows+j]==0)
			{
				for(int m=0; m<height; m++)
				{
					for(int n=0; n<width; n++)
					{
						if(i-height/2>=0&&i+height/2<rows&&j-width/2>=0&&j+width/2<cols)
						{
							if(sd[m*width+n]==1&&src[(i-height/2+m)*rows+j-width/2+n]==0)
								flag = 1;
						}
					}
				}
				if(flag ==0)
					dst[i*rows+j] = src[i*rows+j];
				else
					dst[i*rows+j] = 1;
			}
			else
				dst[i*rows+j] = src[i*rows+j];
		}
	}
	return dst_mat;
}


void hypercv_medianblur(simple_mat dst_mat, simple_mat src_mat,int size)
{
	_assert(!src_mat,"input mat can not be NULL");
	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int data_type = src_mat->data_type;
	int channels = src_mat->channels;
	if(dst_mat == NULL)
		dst_mat = create_simple_mat(rows,cols,data_type,channels);

	unsigned char* src_data = (unsigned char*) src_mat->data;
	unsigned char* dst_data = (unsigned char*) dst_mat->data;
	unsigned char* arr = (unsigned char*) malloc(size*size*sizeof(char));

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if((i-size/2)>=0&&(i+size/2)<rows&&(j-size/2)>=0&&(j+size/2)<cols)
			{
				for(int m = -size/2;m<size/2;m++)
					for(int n = -size/2; n<size/2;n++)
						arr[(m+size/2)*size+n+size/2] = src_data[(i+m)*cols+j+n];

				dst_data[i*cols+j] = median_member(arr,size); 
			}
		}
	}
}

