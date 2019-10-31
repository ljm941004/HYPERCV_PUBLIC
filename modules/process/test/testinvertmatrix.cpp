/*************************************************************************
	> File Name: testinvertmatrix.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;


void test_invert_matrix()
{
	float res1[3][3];
	float mat1[3][3]={{1,2,4},{2,2,2},{1,3,2}};
	
	float* res = &res1[0][0];
	float* mat = &mat1[0][0];

	invert_matrix_float(res,mat,3);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			printf("%f,",res[i*3+j]);
}

TEST(PROCESS,INVERT)
{
	test_invert_matrix();
}
