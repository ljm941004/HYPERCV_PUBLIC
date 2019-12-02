/*************************************************************************
	> File Name: process/test/testfilter.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;

void test_gaussian_blur()
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
