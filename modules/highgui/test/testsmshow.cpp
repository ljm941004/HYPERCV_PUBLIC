/*************************************************************************
	> File Name: testsmshow.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
using namespace std;


void test_smshow()
{
printf("debug\n");
simple_mat	src = smread_bmp("/home/ljm/test.bmp");
printf("debug\n");
	smshow("test",src);
}
TEST(HIGHGUI,SMSHOW)
{
	test_smshow();
}
