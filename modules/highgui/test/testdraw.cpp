/*************************************************************************
	> File Name: highgui/test/testdraw.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

void testdrawpoint()
{
	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	
	POINT A = {10,10};
	POINT B = {70,70};
	POINT C = {50,50};

	POINT* v;
	v = &A;

//	vector_push_back(v,A);
//	vector_push_back(v,B);
//	vector_push_back(v,C);
	
	RGB_data color = {255,0,0};
	draw_POINT(mat,mat,v,1,color,4);
	smwrite_bmp("res.bmp",mat);
}

void testdrawline()
{
	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	POINT A = {100,10};
	POINT B = {70,70};
	RGB_data color = {0,0,255};
	draw_line(mat,mat,A,B,color,5);
	smwrite_bmp("res.bmp",mat);
}



TEST(HIGHGUI,DRAWPOINT)
{
	testdrawpoint();
}
TEST(HIGHGUI,DRAWLINE)
{
	testdrawline();
}
