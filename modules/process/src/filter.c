/*************************************************************************
	> File Name: filter.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void hypercv_filter(simple_mat src, simple_mat dst, unsigned char* kernel, int k_rows, int k_cols, int border_type)
{
	_assert(src!= NULL,"input mat cannot be null");
	_assert(kernel!=NULL,"kernel cannot be null");

	int rows = src->rows;
	int cols = src->cols;
	int channels = src->channels;
	int data_type = src->data_type;

	_assert(data_type == 1,"filter only use in data_type == 1");

	if(dst == NULL)
		dst = create_simple_mat(rows,cols,data_type,channels);

	unsigned char* src_data = (unsigned char*)src->data;
	unsigned char* dst_data = (unsigned char*)dst->data;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{

			



		}



	}




}
