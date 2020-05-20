/*************************************************************************
	> File Name: cem.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"


simple_mat hyper_mat_cem(hyper_mat bsq_mat, float* spectral)
{
	hypercv_assert(bsq_mat->data_type == 4,"input mat data_type is float");
	hypercv_assert(cmpstr(bsq_mat->interleave,"bsq"),"input mat interleave is bsq");
	int samples = bsq_mat -> samples;
	int lines = bsq_mat -> lines;
	int bands = bsq_mat -> bands;
	int data_type = bsq_mat -> data_type;

	simple_mat src = reshape_hypermat_2_simplemat(bsq_mat,bands,samples*lines);
	simple_mat t = create_simple_mat(src->cols,src->rows,data_type,1);
    simple_mat_transport(t,src);
	simple_mat corrmat = create_simple_mat(bands,bands,data_type,1);
	
	float* src_data = (float*)src->data;
	float* t_data = (float*)t->data;
	float* c_data = (float*)corrmat->data;

	correlation_matrix_float(c_data,src_data,t_data,bands,samples*lines,bands);

	simple_mat invmat = create_simple_mat(bands,bands,data_type,1);
	float* invdata = (float*)invmat->data;

	invert_matrix_float(invdata,c_data,bands);

	float* fir1 = (float*)malloc(bands*sizeof(float));
	float* fir2 = (float*)malloc(bands*sizeof(float));
	float* fir3 = (float*)malloc(sizeof(float));

	MulMatrix_float(fir1,invdata,spectral,bands,bands,1);
	MulMatrix_float(fir2,spectral,invdata,1,bands,bands);
	MulMatrix_float(fir3,fir2,spectral,1,bands,1);

	for(int i=0;i<bands;i++)
		fir1[i] = fir1[i]/fir3[0];
	
	simple_mat res = create_simple_mat(lines,samples,data_type,1);
	float* res_data = (float*) res->data;

	MulMatrix_float(res_data,t_data,fir1,samples*lines,bands,1);

	delete_simple_mat(src);
	delete_simple_mat(t);
	delete_simple_mat(corrmat);
	delete_simple_mat(invmat);
	free(fir1);fir1 = NULL;
	free(fir2);fir2 = NULL;
	free(fir3);fir3 = NULL;
	return res;
}

