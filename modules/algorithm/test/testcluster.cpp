/*************************************************************************
	> File Name: modules/algorithm/test/testcluster.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

void testkmeans()
{
	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	
	POINT* v;
	POINT t;
	vector_push_back(v,t);
	vector_push_back(v,t);
	vector_push_back(v,t);
	vector_push_back(v,t);
	hypercv_k_means(mat,v,4,1);
	RGB_data color = {255,0,0};
	
	draw_POINT(mat,mat,v,4,color,10);
	smwrite_bmp("res.bmp",mat);
}

TEST(ALGORITHM,KMEANS)
{
   testkmeans();
}
