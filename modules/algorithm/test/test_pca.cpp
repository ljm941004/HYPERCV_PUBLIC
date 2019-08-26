/*************************************************************************
	> File Name: test_pca.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;
#ifndef TEST_HYPERCV_PERFORMANCE
#define ITERS 1
#else
#define ITES 20
#endif

#ifndef TEST_HYPERCV_PERFORMANCE
#define SAMPLES_START 10
#define SAMPLES_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  10
#define BANDS_END    11

#else
#define SAMPLES_START 10
#define SAMPLES_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  10
#define BANDS_END    11
#endif

static hyper_mat src_mat = NULL;
static hyper_mat dst_mat = NULL;


static void hypercv_test_setup(int samples, int lines, int bands, int data_type, char interleave[])
{
  	src_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
	hypercv_dataInit<unsigned char>((unsigned char*)src_mat->data,samples,lines,bands);
}

static void test_delete_hyper_mat()
{
	delete_hyper_mat(src_mat);
	delete_hyper_mat(dst_mat);
}


void test_pca()
{
	src_mat = hmread("/home/ljm/sm","/home/ljm/sm.hdr");
    hyper_mat bip_mat = bsq2bip(src_mat);
	dst_mat = hyper_mat_copy(bip_mat);
	hyper_mat_pca(bip_mat,dst_mat,20);
	return;
    hmwrite("pca",dst_mat);
	test_delete_hyper_mat();
}

TEST(ALGORITHM,PCA)
{
	test_pca();

}
