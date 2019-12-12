/*************************************************************************
	> File Name: process/test/testpyramid.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;


void test_make_border()
{

	simple_mat t = smread_bmp("/home/ljm/test.bmp");
	smwrite_bmp("t.bmp",hypercv_copy_make_border(t,10,10,20,20,BORDER_CONSTANT,255));
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

TEST(PROCESS,MAKEBORDER)
{
    test_make_border();
}

