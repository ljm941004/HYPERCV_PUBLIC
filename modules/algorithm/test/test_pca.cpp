/*************************************************************************
	> File Name: test_pca.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;

void test_pca()
{
    hyper_mat t = hmread_with_hdr("/home/ljm/data/dataz/bd0z","/home/ljm/data/dataz/bd0z.hdr");

	hyper_mat float_mat =hyper_mat_ushort2float(t);

	delete_hyper_mat(t);
	hyper_mat dst_mat = hyper_mat_copy(float_mat);
	hyper_mat_pca(float_mat,dst_mat,1);
	hmwrite("pca",dst_mat);
	delete_hyper_mat(float_mat);
	delete_hyper_mat(dst_mat);
}

TEST(ALGORITHM,PCA)
{
	test_pca();
}
