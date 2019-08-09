/*************************************************************************
	> File Name: pca.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void hyper_mat_pca(hyper_mat hmat)
{
	_assert(cmpstr(hmat->interleave,"bsq")==1,"hmat interleave must be bsq");
	int samples = hmat->samples;
	int lines = hmat->lines;
	int bands = hmat->bands;
	simple_mat smat = reshape_hypermat_2_simplemat(hmat,bands,samples*lines);

	simple_mat_pca(smat);
}

void simple_mat_pca(simple_mat mat)
{
	_assert(mat!=NULL, "mat can not be null");

	




}
