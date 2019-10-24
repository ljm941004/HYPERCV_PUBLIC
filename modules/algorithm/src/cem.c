/*************************************************************************
	> File Name: cem.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"


void cem(float* res, hyper_mat bsq_mat, float* spectral)
{
	//todo fix float
	int samples = bsq_mat -> samples;
	int lines = bsq_mat -> lines;
	int bands = bsq_mat -> bands;
	int data_type = bsq_mat -> data_type;

	simple_mat src = reshape_hypermat_2_simplemat(bsq_mat,bands,samples*lines);

	simple_mat t = create_simple_mat(samples*lines,bands,data_type,1);

    simple_mat_transport(t,src);

	simple_mat corrmat = create_simple_mat(bands,bands,data_type,1);

	//todo fix only float
	//
	float* src_data = (float*)src->data;
	float* t_data = (float*)t->data;
	float* c_data = (float*)corrmat->data;

	correlation_matrix_float(c_data,src_data,t_data,bands,samples*lines,bands);



}


 



