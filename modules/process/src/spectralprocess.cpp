#include "precomp.h"

/**
* @brief      using known spectrum to match all image. 
* @param[in]  bip_data    bip image data.
* @param[in]  spectrum    match spectrum.
* @param[in]  threshold   threshold of match, default 0.8.
**/
simple_mat spectrum_SAM_match(hyper_mat bip_mat, int spectrum[], float threshold)
{
	_assert(bip_mat != NULL,                       "input hyper mat must not be NULL");
	_assert(cmpstr(bip_mat->interleave,"bip") == 1,"hyper mat interleave should be bip");
	_assert(spectrum != NULL,                      "spectrum must not be NULL");

	int samples = bip_mat -> samples;
	int lines = bip_mat -> lines;
	int bands = bip_mat -> bands;
	int elem_size = get_elem_size(bip_mat->data_type);

	simple_mat match_image;
	match_image = create_simple_mat(lines,samples,1,1);
	

	//todo  fix next 
	char* bip;
	int * sp = spectrum;

	int * bip_point_data = (int *)malloc(bands * sizeof(int));
	memset(bip_point_data, 0, sizeof(int) * bands);

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < samples; j++)
		{
			bip = (char *)bip_mat -> data + (i * samples * bands + j * bands) * elem_size;
			for (int k = 0; k < bands; k++ )
			{

		
			}

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
int* read_spectrum_file(const char* sp_path, int length)
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

