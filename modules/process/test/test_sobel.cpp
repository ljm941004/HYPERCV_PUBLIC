/*************************************************************************
	> File Name: test_sobel.cpp
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

#else
#define SAMPLES_START 10
#define SAMPLES_END   11
#define LINES_START  10
#define LINES_END    11
#endif

static simple_mat src_mat = NULL;
static simple_mat dst_mat = NULL;

static void hypercv_test_setup(int samples, int lines, int bands, int data_type, char interleave[])
{
  	src_mat = create_simple_mat(lines, samples, data_type, 1);
	hypercv_dataInit<unsigned char>((unsigned char*)src_mat->data,samples,lines,1);
}

static void test_delete_simple_mat()
{
	delete_simple_mat(src_mat);
	delete_simple_mat(dst_mat);
}

void test_sobel()
{
	src_mat = smread_bmp("/home/ljm/test.bmp");
	simple_mat sm = sm_rgb2gray(src_mat,0);
	simple_mat dsm = create_simple_mat(sm->rows,sm->cols,sm->data_type,sm->channels);
	hypercv_sobel(sm, dsm, 200, 1);
	simple_mat dst_mat  = sm_gray2rgb(dsm);
	smwrite_bmp("t.bmp",dst_mat);
}
TEST(ALGORITHM,SOBEL)
{
	test_sobel();
}

