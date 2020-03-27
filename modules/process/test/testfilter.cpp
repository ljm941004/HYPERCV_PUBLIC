/*************************************************************************
	> File Name: process/test/testfilter.cpp
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
static simple_mat t = NULL;

template<typename type>
static void hypercv_test_setup(int rows, int cols, int data_type, int channels)
{
  	src_mat = create_simple_mat(rows,cols,data_type,channels);
	hypercv_dataInit<type>((type*)src_mat->data,cols,rows,channels);
}

static void test_filter()
{
	hypercv_test_setup<float>(10,10,1,1); 
	simple_mat dst1 = create_simple_mat(10,10,4,1);
	simple_mat dst2 = create_simple_mat(10,10,4,1);
	float opt1[9] = {-1,-1,1,-1,4,-1,1,-1,-1};
	float opt2[9] = {1,-1,-1,-1,4,-1,-1,-1,1};
	hypercv_filter2D(src_mat,dst1,opt1,3,3,0);
	test_show_mat<float>((float*)dst1->data,10,10,1);
	hypercv_filter2D(src_mat,dst2,opt2,3,3,0);
    test_show_mat<float>((float*)dst2->data,10,10,1);
    simple_mat_addition_float(dst1,dst2,dst1);
    test_show_mat<float>((float*)dst1->data,10,10,1);

	

}

static void test_gaussian_blur()
{
	simple_mat t = smread_bmp("/home/ljm/test.bmp");
	simple_mat d = simple_mat_copy(t);
	hypercv_gaussian_blur(t,d,5,5,0,0,1);
    smwrite_bmp("t.bmp",d);
}

TEST(PROCESS,GAUSSIAN)
{
	test_gaussian_blur();

}

TEST(PROCESS,FILTER2D)
{
	test_filter();
}
