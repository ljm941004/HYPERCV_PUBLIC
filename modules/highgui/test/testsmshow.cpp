/*************************************************************************
	> File Name: testsmshow.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
using namespace std;

simple_mat src = NULL;

void test_smshow()
{
	src = smread_bmp("/home/ljm/test.bmp");
	smshow("test",src);
}
TEST(HIGHGUI,SMSHOW)
{
	test_smshow();
}
