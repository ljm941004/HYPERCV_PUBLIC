/*************************************************************************
	> File Name: laplacian.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void hypercv_laplacian(simple_mat src, simple_mat dst, int k_size, int border_type)
{
	_assert(src!=NULL, "input mat can not be NULL");
	
	int cols = src->cols;
	int rows = src->rows;
	int channels = src->channels;
	int data_type = src->data_type;

	if(dst == NULL)
		dst = create_simple_mat(rows,cols,data_type,channels);

	float kernel[9] = {0.f,1.f,0.f,1.f,-4.f,1.f,0.f,1.f,0.f};

	if(k_size == 2)
	{
		for(int i=0;i<9;i++)
			kernel[i] = kernel[i]*2;
	}

}
