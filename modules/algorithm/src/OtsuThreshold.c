/*************************************************************************
	> File Name: OtsuThreshold.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

/**            
 * @brief      calculate the otsu threshold
 * @param[in]  mat               simple mat
 * @retva      int               threshold    
 **/
int hypercv_otsu_threshold(simple_mat mat)
{
	float deltamax = 0;
	int threshold = 0;
	unsigned char * data = mat->data;

	int pixelcount[256] = {0};
	int pixelpro[256] = {0.0};

	int rows = mat->rows;
	int cols = mat->cols;
	int pixelnum = rows*cols;

	for(int i=0; i<pixelnum; i++)
		pixelcount[data[i]]++;

	for(int i=0; i<256; i++)
		pixelpro[i] = (float)pixelcount[i]/pixelnum;

	for(int i=0; i<256; i++)
	{
		float w0=0.0, w1=0.0, u0tmp=0.0, u1tmp=0.0, u0=0.0, u1=0.0, u=0.0;
		float delta = 0.0;
		for(int j=0; j<256; j++)
		{
			if(j<=i)
			{
				w0 += pixelpro[j];
				u0tmp += j*pixelpro[j];	
			}
			else
			{
				w1 += pixelpro[j];
				u1tmp += j*pixelpro[j];
			}
		}
		u0 = u0tmp/w0;
		u1 = u1tmp/w1;
		u = u0tmp + u1tmp;

		delta = w0*w1*(u0-u1)*(u0-u1);

		if(delta > deltamax)
		{
			deltamax = delta;
			threshold = i;
		}
	}
	return threshold;
}
