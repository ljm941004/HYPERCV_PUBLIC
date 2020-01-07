/*************************************************************************
	> File Name: highgui/src/draw.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"



void draw_POINT(simple_mat mat , POINT* v)
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

	while(iter!=NULL)
	{
	//todo
	}

}

