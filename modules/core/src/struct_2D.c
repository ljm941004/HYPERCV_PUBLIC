/*************************************************************************
	> File Name: 2D_struct.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

/**
 * @brief	   create a 2 dimension struct use in morphology process. 
 * @param[in]  width 	    2D struct width.
 * @param[in]  height  	    2D struct height.
 * @retval     S_2D         2 dimension struct. 
 **/
S_2D create_2D_struct(int width, int height)
{
	hypercv_assert(width>=1 && height>=1, "2D struct's width or height must bigger than 0");
	
	unsigned char * data = (unsigned char*)malloc(width * height * sizeof(unsigned char));
	
	for(int i=0; i<width*height; i++)
		data[i] = 1;
	
	S_2D s = create_2D_struct_with_data(width, height, data);
	
	return s;
}

/**
 * @brief	   create a 2 dimension struct use in morphology process. 
 * @param[in]  width 	    2D struct width.
 * @param[in]  height  	    2D struct height.
 * @param[in]  data   	    2D struct data.
 * @retval     S_2D         2 dimension struct. 
 **/
S_2D create_2D_struct_with_data(int width, int height, void* data)
{
	hypercv_assert(width>=1 && height>=1, "2D struct's width or height must bigger than 0");

	int memneeded = sizeof(STRUCT_2D);
	
	S_2D s;
	s = (S_2D)malloc(memneeded);
	hypercv_assert(s != NULL ,"fail to build 2d_struct");

	s->data = data;
	s->width = width;
	s->height = height;
}

/**
 * @brief	   delete a 2 dimension struct. 
 * @param[in]  s 	    2D struct .
 **/
void delete_S_2D(S_2D s)
{
	if (s==NULL)
		return;

	free(s);
	s = NULL;
}
