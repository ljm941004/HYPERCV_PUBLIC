/*************************************************************************
    > File Name: testdatatypechange.cpp
    > Author: ljm
    > Mail: jimin@iscas.ac.cn 
 ************************************************************************/
#include "precomp.h"

using namespace std;

void test_my_atof()
{
	const char* w = "2323.1";

	float t = hypercv_atof(w);
//	flaot t2 = atof(w);
	
	

}

TEST(PROCESS,ATOF)
{
	test_my_atof();
}
