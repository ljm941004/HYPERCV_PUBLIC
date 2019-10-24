/*************************************************************************
	> File Name: shapematch.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

static double calc_similar_hu(double* hu1, double* hu2)
{
	double res = 0;
	double tmp1 = 0;
	double tmp2 = 0;
	for(int i=0;i<7;i++)
	{
		tmp1 += fabs(hu1[i]-hu2[i]);
		tmp2 += fabs(hu1[i]+hu2[i]);
	}
	res = 1-tmp1/tmp2;
	return res;

}


void calc_hu_moment(double* hu,simple_mat mat)
{
	if(hu==NULL)
		hu = (double*)malloc(7*sizeof(double));

	_assert(mat!=NULL,"input mat cannot be NULL");

	int cols = mat->cols;
	int rows = mat->rows;
	int data_type = mat->data_type;
	int elem_size = get_elemsize(data_type);
	int step = mat->cols*elem_size; 
	unsigned char *data = (unsigned char*)mat->data;

	double m00=0,m11=0,m20=0,m02=0,m30=0,m03=0,m12=0,m21=0;  //中心矩 
	double x0=0,y0=0;    //计算中心距时所使用的临时变量（x-x'） 
	double u20=0,u02=0,u11=0,u30=0,u03=0,u12=0,u21=0;//规范化后的中心矩
	double t1=0,t2=0,t3=0,t4=0,t5=0;//临时变量， 
	//double Center_x=0,Center_y=0;//重心 
	int Center_x=0,Center_y=0;//重心 
	int i,j;            //循环变量

	//  获得图像的区域重心(普通矩)
	double s10=0,s01=0,s00=0;  //0阶矩和1阶矩  
	for(j=0;j<rows;j++)//y
	{
		for(i=0;i<cols;i++)//x
		{
			s10+=i*data[j*step+i];
			s01+=j*data[j*step+i];
			s00+=data[j*step+i];
		}
	}
	Center_x=(int)(s10/s00+0.5);
	Center_y=(int)(s01/s00+0.5);

	//  计算二阶、三阶矩(中心矩)
	m00=s00; 
	for(j=0;j<rows;j++) 
	{
		for(i=0;i<cols;i++)//x 
		{ 
			x0=(i-Center_x); 
			y0=(j-Center_y); 
			m11+=x0*y0*data[j*step+i]; 
			m20+=x0*x0*data[j*step+i]; 
			m02+=y0*y0*data[j*step+i]; 
			m03+=y0*y0*y0*data[j*step+i];
			m30+=x0*x0*x0*data[j*step+i]; 
			m12+=x0*y0*y0*data[j*step+i]; 
			m21+=x0*x0*y0*data[j*step+i]; 
		} 
	} 

	//  计算规范化后的中心矩: mij/pow(m00,((i+j+2)/2)
	u20=m20/pow(m00,2); 
	u02=m02/pow(m00,2); 
	u11=m11/pow(m00,2);
	u30=m30/pow(m00,2.5); 
	u03=m03/pow(m00,2.5);
	u12=m12/pow(m00,2.5); 
	u21=m21/pow(m00,2.5);

	//  计算中间变量
	t1=(u20-u02); 
	t2=(u30-3*u12); 
	t3=(3*u21-u03); 
	t4=(u30+u12);
	t5=(u21+u03);

	//  计算不变矩 
	hu[0]=u20+u02; 
	hu[1]=t1*t1+4*u11*u11; 
	hu[2]=t2*t2+t3*t3; 
	hu[3]=t4*t4+t5*t5;
	hu[4]=t2*t4*(t4*t4-3*t5*t5)+t3*t5*(3*t4*t4-t5*t5); 
	hu[5]=t1*(t4*t4-t5*t5)+4*u11*t4*t5;
	hu[6]=t3*t4*(t4*t4-3*t5*t5)-t2*t5*(3*t4*t4-t5*t5);
}


double hypercv_match_shapes(simple_mat mat1, simple_mat mat2)
{
	_assert(mat1!=NULL&&mat2!=NULL,"input mat cannot be NULL");

	double* hu1 = (double*)malloc(7*sizeof(double));
	double* hu2 = (double*)malloc(7*sizeof(double));

	calc_hu_moment(hu1,mat1);
	calc_hu_moment(hu2,mat2);

	double res=0;
	res = calc_similar_hu(hu1,hu2);
	return res;
}


