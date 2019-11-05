/*************************************************************************
	> File Name: testsmshow.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
using namespace std;

simple_mat src = NULL;

template<typename type>
static void hypercv_test_setup(int samples, int lines, int bands, int data_type, const char interleave[])
{
  	src = create_simple_mat(lines,samples,1,3);
	hypercv_dataInit<type>((type*)src->data,samples,lines,bands);
	
}
void test_smshow()
{
	src = smread_bmp("/home/ljm/bb.bmp");
	smshow("test",src);
}
TEST(HIGHGUI,SMSHOW)
{
	test_smshow();
}
