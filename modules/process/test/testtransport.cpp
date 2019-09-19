/*************************************************************************
	> File Name: testtransport.cpp
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
#define SAMPLES_END   1024
#define LINES_START  10
#define LINES_END    1024
#define BANDS_START  10
#define BANDS_END    1024
#endif

static hyper_mat src_mat = NULL;
static hyper_mat dst_mat = NULL;

static simple_mat s_mat = NULL;
static simple_mat d_mat = NULL;

template<typename type>
static void hypercv_test_setup(int samples, int lines, int bands, int data_type, const char interleave[])
{
	src_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
	hypercv_dataInit<type>((type*)src_mat->data,samples,lines,bands);
	dst_mat = create_hyper_mat(lines,samples,bands,data_type,interleave);

	s_mat = create_simple_mat(lines,samples,data_type,1);
	hypercv_dataInit<type>((type*)s_mat->data,samples,lines,1);
	d_mat = create_simple_mat(samples,lines,data_type,1);
}

static void test_delete_hyper_mat()
{
	if(src_mat!=NULL)
		delete_hyper_mat(src_mat);
	if(dst_mat!=NULL)
		delete_hyper_mat(dst_mat);
	if(s_mat!=NULL)
		delete_simple_mat(s_mat);
	if(d_mat!=NULL)
		delete_simple_mat(d_mat);

}

static void test_hyper_mat_transport()
{
	hypercv_test_setup<float>(3,3,3,4,"bsq");
	hyper_mat_transport(dst_mat,src_mat);
	test_show_mat<float>((float*)src_mat->data,3,3,3);
	test_show_mat<float>((float*)dst_mat->data,3,3,3);
	test_delete_hyper_mat();
}

static void test_simple_mat_transport()
{
	hypercv_test_setup<float>(3,3,3,4,"bsq");
	simple_mat_transport(d_mat,s_mat);
	test_show_mat<float>((float*)s_mat->data,3,3,1);
	test_show_mat<float>((float*)d_mat->data,3,3,1);
	test_delete_hyper_mat();
}

TEST(PROCESS,TRANSPORT)
{
	test_simple_mat_transport();
}
