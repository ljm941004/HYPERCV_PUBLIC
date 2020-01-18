/*************************************************************************
	> File Name: testsmshow.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
using namespace std;


void test_smshow()
{
    simple_mat	src = smread_bmp("/home/ljm/test.bmp");
	smshow("/home/ljm/test.bmp",src);
}
TEST(HIGHGUI,SMSHOW)
{
	test_smshow();
}
