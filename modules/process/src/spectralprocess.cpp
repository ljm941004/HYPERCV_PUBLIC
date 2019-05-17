#include "core.h"

/**
* @brief      using known spectrum to match all image. 
* @param[in]  bip_data    bip image data.
* @param[in]  spectrum    match spectrum.
* @param[in]  samples     bip image samples.
* @param[in]  lines       bip image lines.
* @param[in]  bands       bip image bands.
* @param[in]  threshold   threshold of match, default 0.8.
**/
unsigned char* spectrummatch(unsigned short * bip_data, unsigned short* spectrum, int samples, int lines, int bands, float threshold)
{
	unsigned char* match_image;
	match_image = (unsigned char*)malloc(samples*lines);

	unsigned short* bip = bip_data;

	for (int i=0; i<lines; i++)
	{
		for (int j=0; j<samples; j++)
		{
			float temp = spectral_angle_mapper(bip, spectrum, bands);

			if (temp>threshold)
				match_image[i*samples+j] = 1;
			else
				match_image[i*samples+j] = 0;

			*bip += bands;
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
float spectral_angle_mapper(unsigned short* x, unsigned short* y, int length)
{
	_assert(x != NULL && y != NULL, "spectral angle mapper input must not be NULL");

	float XY = 0.0, X = 0.0, Y = 0.0;

	float res =0.0;

	for (int i=0; i<length; i++)
	{
		XY +=  abs(*x * *y);
		X += (*x)^2;
		Y += (*y)^2;
	}

	res = acos(XY/sqrt(X*Y));

}

/**
* @brief      read spectrum from txt file. 
* @param[in]  sp_path     spectrum file path.
* @param[in]  length      length of spectrum.
**/
unsigned short* readspectrum(const char* sp_path, int length)
{
	FILE *fp = fopen(sp_path,"r");

	_assert(fp != NULL, "spectrum file can not open");

	unsigned short* spectrum = (unsigned short*)malloc(length*sizeof(unsigned short));

	unsigned short* sp = spectrum;

	int temp=0;

	while (fscanf(fp,"%d",&temp) != EOF)
	{
		*sp = temp;
		sp++;
	}

	fclose(fp);

	return spectrum;

}

