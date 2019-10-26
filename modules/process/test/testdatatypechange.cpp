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

	double t = my_atof(w);

	cout<< t<<endl;

}

TEST(PROCESS,ATOF)
{
	test_my_atof();
}
