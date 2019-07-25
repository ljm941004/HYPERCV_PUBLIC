/*************************************************************************
	> File Name: vim testsimplemat.cpp
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
#define ROWS_START 10
#define ROWS_END   11
#define COLS_START  10
#define COLS_END    11

#else
#define ROWS_START 10
#define ROWS_END   11
#define COLS_START  10
#define COLS_END    11
#endif

static simple_mat src_mat = NULL;
static simple_mat dst_mat = NULL;


static void test_setup(int rows, int cols, int channels, int data_type)
{
  	src_mat = create_simple_mat(rows, cols, channels, data_type);
	hypercv_dataInit<unsigned char>((unsigned char*)src_mat->data,cols,rows,channels);
	dst_mat = create_simple_mat(rows, cols, channels, data_type);
}

static void test_delete_simple_mat()
{
	delete_simple_mat(src_mat);
	delete_simple_mat(dst_mat);
}

TEST(CORE,SMDELETE)
{
	test_delete_simple_mat();
}

