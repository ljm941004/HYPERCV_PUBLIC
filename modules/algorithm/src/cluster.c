/*************************************************************************
	> File Name: cluster.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"


static void k_means_point_init(simple_mat mat, int k) //hypercv_vector point_vector)
{
//todo;



}


void hypercv_k_means(simple_mat src, int kind)
{
	_assert(src!=NULL,"INPUT MAT CANNOT BE Null");
	_assert(kind>=1,"kind must >=1");
	
	simple_mat mat;
	if(src->channels != 1)
		mat = sm_rgb2gray(src,0);
	else
		mat = src;

	int rows = src->rows;
	int cols = src->cols;
	

//	k_means_point_init();


}
