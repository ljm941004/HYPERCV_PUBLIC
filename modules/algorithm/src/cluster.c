/*************************************************************************
	> File Name: cluster.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
//----------------------------------private_function--------------------------


static int distance(POINT p, int i,int j)
{
	return pow((p.x-j),2)+pow((p.y-i),2);
}

//-----------------------------------public function---------------------------

void hypercv_k_means(simple_mat src, POINT* v1, int kind, int iter_threshold)
{
	_assert(src!=NULL,"INPUT MAT CANNOT BE Null");
	_assert(kind>=1,"kind must >=1");
	_assert(vector_size(v1)==kind,"input point vector size == kind");

	simple_mat mat;
	if(src->channels != 1)
		mat = sm_rgb2gray(src,0);
	else
		mat = src;

	int rows = src->rows;
	int cols = src->cols;

	POINT* v2 = (POINT*)malloc(kind*sizeof(POINT)); 

	int* num = (int*)malloc(kind*sizeof(int));	
	srand((unsigned)time(NULL));
	for(int i=0;i<kind;i++)
	{
		int x = rand()%cols;
		int y = rand()%rows;
		v1[i].x = x;
		v1[i].y = y;
		v2[i].x = 0;
		v2[i].y = 0;
		num[i]=0;
	}

	unsigned char* data = (unsigned char*)mat->data;
	
	while(1)
	{

		int flag = 0;

		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)
			{
				if(data[i*cols+j]!=0)
				{
					int min_index=0;
					int min_distance = rows*rows+cols*cols;
					for(int k=0;k<kind;k++)
					{
						if(distance(v1[k],i,j)<min_distance)
						{
							min_distance = distance(v1[k],i,j);
							min_index = k;
						}
					}
					v2[min_index].x+=j;
					v2[min_index].y+=i;
					num[min_index]+=1;
				}
			}
		}
		for(int k=0;k<kind;k++)
		{
			if(num[k]!=0)
			{
			v2[k].x = v2[k].x/num[k];
		    v2[k].y = v2[k].y/num[k];
			}
			if(v2[k].x - v1[k].x>iter_threshold||v2[k].y-v1[k].y>iter_threshold)
				flag = 1;
			v1[k].x = v2[k].x;
			v1[k].y = v2[k].y;
			v2[k].x = 0;
			v2[k].y = 0;
			num[k]=0;
		}
		if(flag == 0)
			break;
	}
	free(v2);
	free(num);

}
