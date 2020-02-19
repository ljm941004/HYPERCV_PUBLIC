/*************************************************************************
	> File Name: threshold.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月09日 星期四 22时13分17秒
 ************************************************************************/
#include "precomp.h"

int otsuThreshold(simple_mat img)
{
	
	int Threshold = 0;//阈值
	int height = img->rows;
	int width  = img->cols;
	int channels  = img->channels;
	int step      = width*channels;
	unsigned char* data  = (unsigned char*)img->data;
	double gSum0;//第一类灰度总值
	double gSum1;//第二类灰度总值
	double N0 = 0;//前景像素数
	double N1 = 0;//背景像素数
	double u0 = 0;//前景像素平均灰度
	double u1 = 0;//背景像素平均灰度
	double w0 = 0;//前景像素点数占整幅图像的比例为ω0
	double w1 = 0;//背景像素点数占整幅图像的比例为ω1
	double u = 0;//总平均灰度
	double tempg = -1;//临时类间方差
	double g = -1;//类间方差
	double Histogram[256]={0};// = new double[256];//灰度直方图
	double N = width*height;//总像素数
	for(int i=0;i<height;i++)
	{//计算直方图
		for(int j=0;j<width;j++)
		{
			double temp =data[i*step + j * 3] * 0.114 + data[i*step + j * 3+1] * 0.587 + data[i*step + j * 3+2] * 0.299;
			temp = temp<0? 0:temp;
			temp = temp>255? 255:temp;
			Histogram[(int)temp]++;
		} 
	}
	//计算阈值
	for (int i = 0;i<256;i++)
	{
		gSum0 = 0;
		gSum1 = 0;
		N0 += Histogram[i];			
		N1 = N-N0;
		if(0==N1)break;//当出现前景无像素点时，跳出循环
		w0 = N0/N;
		w1 = 1-w0;
		for (int j = 0;j<=i;j++)
		{
			gSum0 += j*Histogram[j];
		}
		u0 = gSum0/N0;
		for(int k = i+1;k<256;k++)
		{
			gSum1 += k*Histogram[k];
		}
		u1 = gSum1/N1;
		//u = w0*u0 + w1*u1;
		g = w0*w1*(u0-u1)*(u0-u1);
		if (tempg<g)
		{
			tempg = g;
			Threshold = i;
		}
	}
	return Threshold; 
}

void hypercv_threshold_binary(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
	_assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]>thresh)
			dst_data[i] = max_value;
		else
			dst_data[i] = 0;
	}
}

void hypercv_threshold_binary_inv(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]<=thresh)
			dst_data[i] = max_value;
		else
			dst_data[i] = 0;
	}
}

void hypercv_threshold_trunc(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]>thresh)
			dst_data[i] = thresh;
		else
			dst_data[i] = src_data[i];
	}
}

void hypercv_threshold_tozero(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]>thresh)
			dst_data[i] = src_data[i];
		else
			dst_data[i] = 0;
	}
}

void hypercv_threshold_tozero_inv(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value)
{
    _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;

	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]<=thresh)
			dst_data[i] = src_data[i];
		else
			dst_data[i] = 0;
	}	
}

void hypercv_threshold_mask(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value){}

void hypercv_threshold_otsu(simple_mat src_mat, simple_mat dst_mat)
{
 _assert(src_mat!=NULL&&dst_mat!=NULL,"input mat cannot be NULL");
	_assert(src_mat->rows == dst_mat->rows&&src_mat->cols==dst_mat->cols&&src_mat->channels==dst_mat->channels,"src_mat & dst_mat size equal");
	_assert(src_mat->data_type == 1,"0-255");
	_assert(src_mat->channels == 1, "threshold only use in gray image");


	int rows = src_mat->rows;
	int cols = src_mat->cols;
	int channels = src_mat->channels;
	int thresh = otsuThreshold(src_mat);
		
	unsigned char* src_data = (unsigned char*)src_mat ->data;
	unsigned char* dst_data = (unsigned char*)dst_mat ->data;

	for(int i=0;i<rows*cols*channels;i++)
	{
		if(src_data[i]<thresh)
			dst_data[i] = 0;
		else
			dst_data[i] = 255;
	}	


}

void hypercv_threshold_triangle(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value){}

void hypercv_threshold(simple_mat src_mat, simple_mat dst_mat, int thresh, int max_value, int type)
{
	_assert(src_mat!=NULL,"input mat cannot be NULL");
	_assert(dst_mat!=NULL,"output mat cannot be NULL");
	_assert(type == THRESH_BINARY ||
			type == THRESH_BINARY_INV||
			type == THRESH_TRUNC||
			type == THRESH_TOZERO||
			type == THRESH_TOZERO_INV||
			type == THRESH_MASK||
			type == THRESH_OTSU||
			type == THRESH_TRIANGLE , "threshold type error");

	switch(type)
	{
		case THRESH_BINARY:
			hypercv_threshold_binary(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_BINARY_INV:
			hypercv_threshold_binary_inv(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TRUNC:	
			hypercv_threshold_trunc(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TOZERO:
			hypercv_threshold_tozero(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_TOZERO_INV:
			hypercv_threshold_tozero_inv(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_MASK:
			hypercv_threshold_mask(src_mat, dst_mat, thresh, max_value);
			break;
		case THRESH_OTSU:
			hypercv_threshold_otsu(src_mat, dst_mat);
			break;
		case THRESH_TRIANGLE:
			hypercv_threshold_triangle(src_mat, dst_mat, thresh, max_value);
			break;
	}
}
