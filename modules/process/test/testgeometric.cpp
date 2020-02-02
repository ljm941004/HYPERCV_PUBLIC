/*************************************************************************
	> File Name: process/test/testpyramid.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;


void test_simple_mat_flip()
{
	simple_mat t = smread_bmp("/home/ljm/test.bmp");	
    simple_mat d = create_simple_mat(t->rows, t->cols, t->data_type, t->channels);

	simple_mat_flip(t,d,-1);
	smshow("d",d);

}

void test_pyramid_up()
{
	simple_mat t = smread_bmp("/home/ljm/test.bmp");	
    simple_mat d = create_simple_mat(t->rows*2,t->cols*2,t->data_type,t->channels);
	hypercv_pyramid_up(t,d);
    smwrite_bmp("t.bmp",d);
}

TEST(PROCESS,PYRAMIDUP)
{
	test_pyramid_up();
}

TEST(PROCESS,FLIP)
{
	test_simple_mat_flip();
}
