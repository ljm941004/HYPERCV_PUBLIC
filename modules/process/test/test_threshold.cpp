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
	simple_mat d = sm_rgb2gray(mat,0);
	simple_mat c = simple_mat_copy(d);
	hypercv_threshold(d,c,0,255,8);
	simple_mat dst = sm_gray2rgb(c);
	smwrite_bmp("res.bmp",dst);
	
}

TEST(PROCESS,OTSU)
{
	test_otsu_threshold();
}
