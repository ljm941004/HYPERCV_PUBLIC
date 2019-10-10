/*************************************************************************
	> File Name: savesm.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

simple_mat bmp2sm(char *bmpName, RGBQUAD *pColorTable)
{
	FILE *fp = fopen(bmpName, "rb");
	if (NULL == fp)
	{
		printf("There is no fp!!!\n");
		return 0;
	}
 
	fseek(fp, sizeof(FileHeader), SEEK_SET);
	InfoHeader head;
	fread(&head, sizeof(InfoHeader), 1, fp);
 
	int bmpWidth = head.biWidth;
	int bmpHeight = head.biHeight;
	int biBitCount = head.biBitCount;
 
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	if (biBitCount == 8)
	{
		pColorTable = (RGBQUAD *)malloc(sizeof(RGBQUAD) * 1024);
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	unsigned char* pBmpBuf = (unsigned char *)malloc(sizeof(unsigned char) * lineByte * bmpHeight);
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	fclose(fp);

	simple_mat res = create_simple_mat_with_data(bmpHeight,bmpWidth,1,3,pBmpBuf);

	return res;
}




int sm2bmp(char *bmpName, simple_mat src_mat, RGBQUAD *pColorTable)
{
	unsigned char* imgBuf = (unsigned char*) src_mat->data;
	int width = src_mat -> cols;
	int height = src_mat -> rows;

	int data_type = src_mat -> data_type;
	int biBitCount = 24;

	if(imgBuf == NULL)
	{
		printf("imgBuf is NULL!!\n");
		return -1;
	}
 
	int colorTablesize = 0;
	if (biBitCount == 8)
	{
		colorTablesize=1024;
	}
	
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
 
	FILE *fp = fopen(bmpName, "wb");
	if (fp == NULL)
	{
		printf("fopen error...\n");
		return -1;
	}
	
	FileHeader fileHead;
	fileHead.bfType=0x4D42;
 
	fileHead.bfSize = sizeof(FileHeader) + sizeof(InfoHeader) + colorTablesize + lineByte * height;
	
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
 
	fileHead.bfOffBits = 54 + colorTablesize;
 
	fwrite(&fileHead, sizeof(FileHeader), 1, fp);
 
	InfoHeader infoHead;
	infoHead.biBitCount = biBitCount;
	infoHead.biClrImportant = 0;
	infoHead.biClrUsed = 0;
	infoHead.biCompression = 0;
	infoHead.biHeight = height;
	infoHead.biPlanes = 1;
	infoHead.biSize = 40;
	infoHead.biSizeImage = lineByte * height;
	infoHead.biWidth = width;
	infoHead.biXPelsPerMeter = 0;
	infoHead.biYPelsPerMeter = 0;
 
	fwrite(&infoHead, sizeof(InfoHeader), 1, fp);
 
	if (biBitCount == 8)
	{
		fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	}
	
	fwrite(imgBuf, height * lineByte, 1, fp);
 
	fclose(fp);
	
	return 0;
}

