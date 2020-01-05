/*************************************************************************
	> File Name: modules/core/test/testvector.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月04日 星期六 22时55分28秒
 ************************************************************************/
#include "precomp.h"


void test_hypercv_vector()
{
	hypercv_vector cv = hypercv_vector_create(sizeof(int));

	int temp = 4;

	hypercv_vector_pushback(cv,&temp);

	hypercv_vector_print(cv);

}

TEST(CORE,VECTOR)
{
	test_hypercv_vector();
}

