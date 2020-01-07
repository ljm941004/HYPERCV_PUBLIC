/*************************************************************************
	> File Name: testvector.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void testvector()
{
	POINT* v;

	POINT a{1,2};
	POINT b{1,2};
	POINT c{1,2};
	vector_push_back(v,a);
	vector_push_back(v,b);
	vector_push_back(v,c);
}

TEST(CORE,VECTOR)
{
	testvector();

}
