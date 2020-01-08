/*************************************************************************
	> File Name: highgui/test/testdraw.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

void testdrawpoint()
{
	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	POINT* v;
	POINT  A = {10,10};
	POINT  B = {70,70};
	POINT  C = {50,50};
	vector_push_back(v,A);
	vector_push_back(v,B);
	vector_push_back(v,C);
	RGB_data color = {255,0,0};
	draw_POINT(mat,v,color,5);
	smwrite_bmp("res.bmp",mat);
}

TEST(HIGHGUI,DRAWPOINT)
{
	testdrawpoint();
}
