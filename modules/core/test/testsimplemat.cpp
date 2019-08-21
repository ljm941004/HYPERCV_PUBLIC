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
#define ROWS_END   100
#define COLS_START  10
#define COLS_END    100

#else
#define ROWS_START 10
#define ROWS_END   11
#define COLS_START  10
#define COLS_END    11
#endif

static simple_mat src_mat = NULL;
static simple_mat dst_mat = NULL;
static simple_mat t =NULL;
	template<typename type>
static void test_setup(int rows, int cols, int channels, int data_type)
{
	src_mat = create_simple_mat(rows, cols, channels, data_type);
	hypercv_dataInit<type>((unsigned char*)src_mat->data,cols,rows,channels);
	dst_mat = create_simple_mat(rows, cols, channels, data_type);
}

static void test_delete_simple_mat()
{
	if(src_mat!=NULL)
		delete_simple_mat(src_mat);
	if(dst_mat!=NULL)
		delete_simple_mat(dst_mat);
	if(t!=NULL)
		delete_simple_mat(t);
}

static void test_simple_mat_copy()
{
	for(int i=ROWS_START;i<ROWS_END;i++)
	{
		for(int j=COLS_START;j<COLS_END;j++)
		{
			test_setup<unsigned char>(i,j,1,1);
			t = simple_mat_copy(src_mat);
			int tmp = hypercv_mat_compare<unsigned char>((unsigned char*)t->data,(unsigned char*)src_mat->data,j,i,1);
			_assert(tmp==0,"wrong");
			test_delete_simple_mat;
		}
	}

}

void test_sm_save_2_bmp()
{
	test_setup<unsigned char>(1080,1080,1,1);

	sm_save_2_bmp("test.bmp",src_mat);
	test_delete_simple_mat;
}


TEST(CORE,SMCOPY)
{
	test_simple_mat_copy();
}

TEST(CORE,SMDELETE)
{
	test_delete_simple_mat();
}

TEST(CORE,SMSAVE)
{
	test_sm_save_2_bmp();
}

