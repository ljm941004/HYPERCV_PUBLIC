#pragma once 

#include <iostream>
#include <sys/time.h>
#include <math.h>

/*-------------------------------------------
 *                 data init 
 *------------------------------------------*/

template<typename type>
void hypercv_dataInit(type* mat, int samples, int lines, int bands)
{
	int i,j,k;
	for(k=0; k<bands; k++)
	{
		for(i=0; i<lines; i++)
		{
			for(j=0; j<samples; j++)
			{
				double data = drand48();
				data = data * 13.27680f - 1.63840f;

				data = fabs(data);
				
				data = (type)(data);

				mat[lines*samples*k+ i*samples + j]=data;
			}

		}
	}

}

/*--------------------------------
 *         result confirm
 * ------------------------------*/

template<typename type>
int hypercv_mat_compare(type * mat1,type* mat2, int samples, int lines,int bands)
{
	int flag = 0;

	int i,j,k;
	for(k=0; k<bands; k++)
	{
		for(i=0; i<lines; i++)
		{
			for(j=0; j<samples; j++)
			{
				type d1 = mat1[k*samples*lines+i*samples+j];
				type d2 = mat2[k*samples*lines+i*samples+j];
				if((std::isnan((float)d1)^std::isnan((float)d2))==1)
				{
					std::cout <<"ERROR:";
					std::cout <<"bands:"<<k<<"samples:"<<j<<"lines:"<<i;
					std::cout <<"mat1:"<<d1;
					std::cout <<"mat2:"<<d2;

					flag =1;
				}
				if(flag == 1)
					return flag;
			}
		}
	}
	return flag;
}

/*-------------------------------------------
 *              show mat
 * -----------------------------------------*/
	template<typename type>
void test_show_mat(type *mat, int samples, int lines, int bands)
{
	for(int i=0; i<bands;i++)
	{
		for(int j=0;j<lines;j++)
		{
			for(int k=0;k<samples;k++)
			{
				if(sizeof(type) == 1||sizeof(type)==2)
				{
					int tmp = mat[i*samples*lines+j*samples+k];
					std::cout<<tmp<<" ";
				}
				else
				{
					double t = mat[i*samples*lines+j*samples+k];
					std::cout<<t<<" ";
				}
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
		std::cout<<std::endl;
	}
}

	template<typename type>
void test_show_mat_bip(type *mat, int samples, int lines, int bands)
{
	for(int i=0; i<lines;i++)
	{
		for(int j=0;j<samples;j++)
		{
			for(int k=0;k<bands;k++)
			{

				std::cout<<mat[i*samples*bands + j*bands + k]<<" ";

			}
			std::cout<<"  ";
		}
		std::cout<<std::endl;
	}
}


