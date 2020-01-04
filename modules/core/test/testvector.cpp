/*************************************************************************
	> File Name: modules/core/test/testvector.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月04日 星期六 22时55分28秒
 ************************************************************************/
#include "precomp.h"


void test_hypercv_vector()
{
	hypercv_vector cv = hypercv_vector_create(5);

	POINT T1,T2,T3,T4,T5;
	hypercv_vector_pushback(cv,&T1);
	hypercv_vector_pushback(cv,&T2);
	hypercv_vector_pushback(cv,&T3);
	hypercv_vector_pushback(cv,&T4);
	hypercv_vector_pushback(cv,&T5);

	hypercv_vector_info(cv);
	hypercv_vector_destroy(cv);

}

TEST(CORE,VECTOR)
{
	test_hypercv_vector();
}

