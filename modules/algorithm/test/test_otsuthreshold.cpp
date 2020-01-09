/*************************************************************************
	> File Name: algorithm/test/test_otsuthreshold.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月09日 星期四 20时23分03秒
 ************************************************************************/
#include "precomp.h"

void test_otsu_threshold()
{
	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	printf("%d", hypercv_otsu_threshold(mat));
	
}
TEST(ALGORITHM,OTSU)
{
	test_otsu_threshold();
}
