/*************************************************************************
	> File Name: morphology.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

//only data_type unsigned char 

//_____________________public function_________________________

/**
 * @brief      simple_mat corrosion with 2D struct.
 * @param[in]  simple_mat    2d image mat.
 * @param[in]  S_2D          2D struct.
 **/
void hypercv_corrosion(simple_mat mat, simple_mat dst_mat, S_2D s)
{
	_assert(mat!=NULL,"input mat cannot be NULL");
	_assert(s!= NULL, "corrosion kernel cannot be NULL");

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
		return;
	}	

	if(dst_mat == NULL)
		dst_mat = simple_mat_copy(mat);

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
}


/**
 * @brief      simple_mat expend with 2D struct.
 * @param[in]  simple_mat    2d image mat.
 * @param[in]  S_2D          2D struct.
 * @retval     simple_mat    2d image mat.
 **/
void hypercv_expend(simple_mat mat, simple_mat dst_mat, S_2D s)
{
	_assert(mat!=NULL,"input mat cannot be NULL");
	_assert(s!= NULL, "expend kernel cannot be NULL");

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
		return;
	}	

	if(dst_mat == NULL)
		dst_mat = simple_mat_copy(mat);

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
}

//todo fix 
void hypercv_open(simple_mat src, simple_mat dst, S_2D kernel, int iterations)
{
	_assert(src!= NULL,"input mat cannot be NULL");
	_assert(kernel != NULL, "kernel cannot be NULL");

	int rows = src->rows;
	int cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

	if(dst == NULL)
		dst = simple_mat_copy(src);

	for(int i=0;i<iterations;i++)
	{
	    hypercv_corrosion(src,dst,kernel);
		hypercv_expend(src,dst,kernel);
	}
}

void hypercv_close(simple_mat src, simple_mat dst, S_2D kernel, int iterations)
{
	_assert(src!= NULL,"input mat cannot be NULL");
	_assert(kernel != NULL, "kernel cannot be NULL");

	int rows = src->rows;
	int cols = src->cols;
	int data_type = src->data_type;
	int channels = src->channels;

	if(dst == NULL)
		dst = simple_mat_copy(src);

	for(int i=0;i<iterations;i++)
	{
		hypercv_expend(src,dst,kernel);
	    hypercv_corrosion(src,dst,kernel);
	}
}



