/*************************************************************************
	> File Name: test_linear_tension.cpp
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

template<typename type>
static void hypercv_test_setup(int samples, int lines, int bands, int data_type, const char interleave[])
{
  	src_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
	hypercv_dataInit<type>((type*)src_mat->data,samples,lines,bands);
	dst_mat = create_hyper_mat(samples,lines,bands,1,interleave);
}

static void test_delete_hyper_mat()
{
	if(src_mat!=NULL)
		delete_hyper_mat(src_mat);
	if(dst_mat!=NULL)
		delete_hyper_mat(dst_mat);
}

void test_linear_tension()
{
	hyper_mat t = create_hyper_mat(3,3,3,4,"bsq");
	if(t->data ==NULL)
		cout<<"r";
    else
	    cout<<"d";
//	hypercv_dataInit<float>((float*)t->data,3,3,3);
	float * m = (float*)t->data;
	std::cout<< m[28];
	
	
	//test_show_mat<float>((float*)src_mat->data,3,3,3);
	test_delete_hyper_mat();
}
TEST(ALGORITHM,LINEAR_TENSION)
{
	test_linear_tension();
}

