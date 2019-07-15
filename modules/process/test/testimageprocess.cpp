#include "precomp.h"
void test_bi12bsq()
{
	const char* image_path = "IMAGE_20180914142522_0030.raw";
	const char* hdr_path = "IMAGE_20180914142522_0030.hdr";

	hyper_mat bil_mat = hmread(image_path);
	hyper_mat bsq_mat = bil2bsq(bil_mat);

	hyper_mat t = bsq2bil(bsq_mat);
	hyper_mat s = bil2bip(t);
	hyper_mat q = bip2bsq(s);

	compare_2_mat(bil_mat,t);

	delate_hyper_mat(bil_mat);
	delate_hyper_mat(bsq_mat);
}

void test_hypermat_get_range()
{
	const char* image_path = "IMAGE_20180914142522_0030.raw";
	const char* hdr_path = "IMAGE_20180914142522_0030.hdr";

	hyper_mat bil_mat = hmread(image_path);
	hyper_mat bsq_mat = bil2bsq(bil_mat);

	hyper_mat t = hyper_mat_get_range(bil_mat,20,20,20,80,80,80);
	hyper_mat s = hyper_mat_get_range(bsq_mat,20,20,20,80,80,80);

	hyper_mat m = bsq2bil(s);
	hyper_mat p = bil2bsq(t);

	compare_2_mat(m,t);
	compare_2_mat(p,s);

	delate_hyper_mat(bil_mat);
    delate_hyper_mat(bsq_mat); 
    delate_hyper_mat(m);
    delate_hyper_mat(p);
    delate_hyper_mat(t);
	delate_hyper_mat(s);
}

void test_reshape_hypermat_2_simplemat()
{
	const char* image_path = "IMAGE_20180914142522_0030.raw";
	const char* hdr_path = "IMAGE_20180914142522_0030.hdr";

	hyper_mat bil_mat = hmread(image_path);
	hyper_mat bsq_mat = bil2bsq(bil_mat);

	simple_mat mat = reshape_hypermat_2_simplemat(bsq_mat, bsq_mat->bands,bsq_mat->samples*bsq_mat->lines);


}
