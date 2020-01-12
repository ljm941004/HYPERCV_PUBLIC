/*************************************************************************
	> File Name: testvector.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void t(POINT* v)
{
	for(int i=0;i<5;i++)
		printf("%d,%d\n",v[i].x,v[i].y);
}

void testvector()
{
    POINT* v;
	int* ss;
	vector_push_back(ss,10);
	vector_push_back(ss,10);
	vector_push_back(ss,10);
	vector_push_back(ss,10);
	srand((unsigned)time(NULL));
	for(int i=0;i<5;i++)
	{
		 int x = rand()%50;
		 int y = rand()%50;
		 POINT tmp{x,y};
		 printf("%d,%d\n",x,y);
		 vector_push_back(v,tmp);
	}
	printf("%zu\n",vector_capacity(ss));
	printf("%zu\n",vector_size(ss));
	t(v);


}

TEST(CORE,VECTOR)
{
	testvector();

}
