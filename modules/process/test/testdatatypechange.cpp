/*************************************************************************
    > File Name: testdatatypechange.cpp
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

static simple_mat src_mat = NULL;
static simple_mat dst_mat = NULL;

template<typename type>
static void hypercv_test_setup(int rows, int cols, int data_type, int channels)
{
  	src_mat = create_simple_mat(rows,cols,data_type,channels);
	hypercv_dataInit<type>((type*)src_mat->data,cols,rows,channels);
	dst_mat = create_simple_mat(rows,cols,1,channels);
}

static void test_delete_hyper_mat()
{
	if(src_mat!=NULL)
		delete_simple_mat(src_mat);
	if(dst_mat!=NULL)
		delete_simple_mat(dst_mat);
}

void test_simple_mat_float2uchar()
{
	hypercv_test_setup<float>(10,10,4,1);
	test_show_mat<float>((float*)src_mat->data,10,10,1);

	simple_mat d = simple_mat_float2uchar(src_mat);

	test_show_mat<unsigned char>((unsigned char*)d->data,10,10,1);

	test_delete_hyper_mat();

}


TEST(PROCESS,SIMPLE_MAT_F2UC)
{
	test_simple_mat_float2uchar();
}
