#include "stdafx.h"

/**
* @brief      using known spectrum to match all image. 
* @param[in]  bip_data    bip image data.
* @param[in]  spectrum    match spectrum.
* @param[in]  threshold   threshold of match, default 0.8.
**/
unsigned char* spectrummatch(hyper_mat bip_mat, int spectrum[], float threshold)
{
	_assert(bip_mat != NULL,                       "input hyper mat must not be NULL");
	_assert(cmpstr(bip_mat->interleave,"bip") == 1,"hyper mat interleave should be bip");
	_assert(spectrum != NULL,                      "spectrum must not be NULL");

	int samples = bip_mat -> samples;
	int lines = bip_mat -> lines;
	int bands = bip_mat -> bands;
	int elem_size = get_elem_size(bip_mat->data_type);

	unsigned char* match_image;
	match_image = (unsigned char*)malloc(samples*lines);

	//todo  fix next 
	char* bip;
	int * sp = spectrum;

	for (int i=0; i<lines; i++)
	{
		for (int j=0; j<samples; j++)
		{
			bip =(char *)bip_mat->data + (i*samples*bands+j*bands) * elem_size;

		}
	}

	return match_image;
}

/**
* @brief      calculate two vector similar. 
* @param[in]  x           vector x.
* @param[in]  y           vector y.
* @param[in]  length      length of two vector.
**/
float spectral_angle_mapper(float * x, float * y, int length)//todo 
{
	_assert(x != NULL && y != NULL, "spectral angle mapper input must not be NULL");

	float XY = 0.0, X = 0.0, Y = 0.0;

	float res =0.0;

	for (int i=0; i<length; i++)
	{
		XY +=  abs(*x * *y);
		X += (*x)*(*x);
		Y += (*y)*(*y);
	}

	res = acos(XY/sqrt(X*Y));
}

/**
* @brief      read spectrum from txt file. 
* @param[in]  sp_path     spectrum file path.
* @param[in]  length      length of spectrum.
**/
int* readspectrum(const char* sp_path, int length)
{
	FILE *fp = fopen(sp_path,"r");

	_assert(fp != NULL, "spectrum file can not open");

	int* spectrum = (int*)malloc(length*sizeof(int));

	int* sp = spectrum;

	int temp=0;

	while (fscanf(fp,"%d",&temp) != EOF)
	{
		*sp = temp;
		sp++;
	}

	fclose(fp);
	return spectrum;
}

