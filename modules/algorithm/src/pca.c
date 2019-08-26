/*************************************************************************
	> File Name: pca.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
//________private function________________

static void cal_covariance_matrix(hyper_mat bip_mat,simple_mat mean_mat,hyper_mat src_mat,simple_mat res_mat)
{//only for float
	
	int samples = src_mat -> samples;
	int lines = src_mat -> lines;
	int bands = src_mat -> bands;

	hyper_mat t = create_hyper_mat(lines,samples,bands,4,"bsq");
	hyper_mat bsq_mat = bip2bsq(bip_mat);
	hyper_mat_reverse(bsq_mat,t);

	float* src_data = (float*)src_mat->data;
	float* mean_data = (float*)mean_mat->data;
	float* res_data = (float*)res_mat->data;
	float* t_data = (float*)t->data;
	for(int i=0;i<samples*lines;i++)
		for (int j=0;j<bands;j++)
			src_data[i*bands+j]-= mean_data[i];	

	MulMatrix_float(t_data,src_data,res_data,bands,lines*samples,bands);

	delete_hyper_mat(t);
	delete_hyper_mat(bsq_mat);
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

	simple_mat cov_mat = create_simple_mat(bands,bands,4,1);
    
	hyper_mat xmat = hyper_mat_copy(bip_mat);
	cal_covariance_matrix(bip_mat,mean_mat,xmat,cov_mat);

	simple_mat temp;
    
	temp = simple_mat_copy(cov_mat);

	simple_mat q_mat = create_simple_mat(cov_mat->rows,cov_mat->cols,4,1);
	simple_mat r_mat = create_simple_mat(cov_mat->rows,cov_mat->cols,4,1); 
	for(int i=0;i<iteration;i++)//迭代
	{
		matrix_QR_float(temp->data,q_mat->data,r_mat->data,bands);
		MulMatrix_float(q_mat->data,r_mat->data,temp->data,bands,bands,bands);
	}
	
	float* evalue = (float*)malloc(bands*sizeof(float));

	for(int k=0;k<bands;k++)
		evalue[k] = ((float*)temp->data)[k*bands+k];
	
	sort_array_down_float(evalue,bands);

	simple_mat eigen_vector = simple_mat_copy(q_mat);

	cal_eigen_vector_float(cov_mat->data,eigen_vector->data,evalue,bands,bands);

	MulMatrix_float(xmat->data,eigen_vector->data,res_bip_mat->data,samples*lines,bands,bands);


	/*

	simple_mat eigen_vector_q = create_simple_mat(samples*lines, bands,4,1);
	   simple_mat reverse_eigen_vector_q = copy_simple_mat(eigen_vector_q);

	TransMatrix_float(eigen_vector_q->data,reverse_eigen_vector_q->data,eigen_vector_q->rows,eigen_vector_q->cols);


*/



}
