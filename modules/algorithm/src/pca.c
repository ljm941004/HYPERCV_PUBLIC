/*************************************************************************
	> File Name: pca.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
//________private function________________

static void cal_covariance_matrix(simple_mat x, simple_mat mean_mat,simple_mat res_mat)
{//only for float

	int samples = mean_mat->cols;
	int lines = mean_mat->rows;
	int bands = x->cols;

	float* x_data = (float*)x->data;
	float* mean_data = (float*)mean_mat->data;
	float* res_data = (float*)res_mat->data;
	
	for(int i=0;i<samples*lines;i++)
		for (int j=0;j<bands;j++)
			 x_data[i*bands+j] -= mean_data[i];

	simple_mat t = create_simple_mat(bands,samples*lines,4,1);
    simple_mat_transport(t,x);

	float* t_data = (float*)t->data;
	
	MulMatrix_float(t_data,x_data,res_data,bands,lines*samples,bands);
	
	delete_simple_mat(t);
}

//------

void hyper_mat_pca(hyper_mat bip_mat,hyper_mat res_bip_mat,int iteration)
{

	_assert(bip_mat->data_type = 4,"only use in float");

	int samples = bip_mat->samples;
	int lines = bip_mat->lines;
	int bands = bip_mat->bands;
	
	simple_mat mean_mat = create_simple_mat(lines,samples,4,1);
	hyper_mat_mean(bip_mat,mean_mat);

	simple_mat x = reshape_hypermat_2_simplemat(bip_mat,samples*lines,bands);
	simple_mat cov_mat = create_simple_mat(bands,bands,4,1);
	cal_covariance_matrix(x,mean_mat,cov_mat);

	simple_mat temp = simple_mat_copy(cov_mat);
	simple_mat q_mat = create_simple_mat(cov_mat->rows,cov_mat->cols,4,1);
	simple_mat r_mat = create_simple_mat(cov_mat->rows,cov_mat->cols,4,1); 

	for(int i=0;i<iteration;i++)//迭代
	{
		matrix_QR_float((float*)temp->data,(float*)q_mat->data,(float*)r_mat->data,bands);
		MulMatrix_float((float*)q_mat->data,(float*)r_mat->data,(float*)temp->data,bands,bands,bands);
	}
	
	float* evalue = (float*)malloc(bands*sizeof(float));

	for(int k=0;k<bands;k++)
		evalue[k] = ((float*)temp->data)[k*bands+k];
	
	sort_array_down_float(evalue,bands);

	simple_mat eigen_vector = simple_mat_copy(q_mat);

	cal_eigen_vector_float((float*)cov_mat->data,(float*)eigen_vector->data,evalue,bands,bands);

	MulMatrix_float((float*)x->data,(float*)eigen_vector->data,(float*)res_bip_mat->data,samples*lines,bands,bands);

	/*
	simple_mat eigen_vector_q = create_simple_mat(samples*lines, bands,4,1);
	   simple_mat transport_eigen_vector_q = copy_simple_mat(eigen_vector_q);

	TransMatrix_float(eigen_vector_q->data,transport_eigen_vector_q->data,eigen_vector_q->rows,eigen_vector_q->cols);
*/
}
