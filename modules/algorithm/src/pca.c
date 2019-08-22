/*************************************************************************
	> File Name: pca.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
//________private function________________

void cal_covariance_matrix(hyper_mat bip_mat,simple_mat mean_mat, simple_mat res_mat)
{//only for float
	hyper_mat src_mat = hyper_mat_copy(bip_mat);
	
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
	delete_hyper_mat(src_mat);
	delete_hyper_mat(bsq_mat);
}
//________________________________________
void hyper_mat_pca(hyper_mat bip_mat)
{
	int samples = hmat->samples;
	int lines = hmat->lines;
	int bands = hmat->bands;

	simple_mat mean_mat = create_simple_mat(lines,samples,4,1);

	hyper_mat_mean(bip_mat,mean_mat);

	simple_mat cov_mat = create_simple_mat(bands,bands,4,1);
    
	cal_covariance_matrix(bip_mat,mean_mat,cov_mat);
	//todo add qr



}
