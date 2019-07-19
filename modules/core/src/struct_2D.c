/*************************************************************************
	> File Name: 2D_struct.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

S_2D create_2D_struct(int width, int height)
{
	_assert(width>=1 && height>=1, "2D struct's width or height must bigger than 0");
	unsigned char * data = (unsigned char*)malloc(width * height * sizeof(unsigned char));
	for(int i=0; i<width*height; i++)
		data[i] = 1;
	S_2D s = create_2D_struct_with_data(width, height, data);
	return s;
}


S_2D create_2D_struct_with_data(int width, int height, unsigned char* data)
{
	_assert(width>=1 && height>=1, "2D struct's width or height must bigger than 0");

	int memneeded = sizeof(STRUCT_2D);
	
	S_2D s;

	s = (S_2D)malloc(memneeded);
	_assert(s != NULL ,"fail to build 2d_struct");

	s->data = data;

	s->width = width;
	s->height = height;
}
