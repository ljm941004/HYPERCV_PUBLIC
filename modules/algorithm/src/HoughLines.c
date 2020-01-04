/*************************************************************************
	> File Name: HoughLines.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"


void hypercv_hough_trans(POINT** points, int point_num, int RMax, int *lineR, int *lineTheta)
{
	//x*cos(theta)+y*sin(theta)=r;
	int k,maxValue;
	int *pAccumulateArr=NULL;		//累加数组
	int thetaMax=360;
	int theta;
	int rValue;
	float fRate = (float)(PI/180);
	int AccuArrLength=(thetaMax+1)*(RMax+1);
/*	
	pAccumulateArr=(int*)malloc(AccuArrLength*sizeof(int));
	memset(pAccumulateArr,0,AccuArrLength*sizeof(int));
	for (k=0;k<pointNum;k++)
	{
		for (theta=0;theta<=thetaMax;theta++)
		{
			rValue=(float)(pPoints[k*2]) * cos(theta * fRate) + float(pPoints[k*2+1]) * sin(theta * fRate)+0.5;
 
			if (rValue>=0)
			{
				int indexTemp=rValue*(thetaMax+1)+theta;
				if (rValue<=RMax && indexTemp>=0)
				{
					pAccumulateArr[indexTemp]++;
				}
			}
		}
	}
	
	//得到最佳参数
	maxValue=0;
	lineR=0;
	lineTheta=0;
	for (rValue=0;rValue<=RMax;rValue++)
	{
		for (theta=0;theta<=thetaMax;theta++)
		{
			int iCount = pAccumulateArr[rValue * (thetaMax+1) + theta];
			if (maxValue<iCount)
			{
				maxValue=iCount;
				lineR=rValue;
				lineTheta=theta;
			}
		}
	}
	
	free(pAccumulateArr);
	pAccumulateArr=0;
	
	if (maxValue!=0)
	{
		
		return true;
	}
	else
	{
		return false;
	}
*/
	}

