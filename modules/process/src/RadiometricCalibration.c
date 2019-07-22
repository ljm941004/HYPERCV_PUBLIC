#include "precomp.h"

hyper_mat relative_radiometric_correction(hyper_mat bip_mat, float* coefficient)
{
	int samples = bip_mat->samples;
	int lines = bip_mat->lines;
	int bands = bip_mat->bands;

	unsigned short * bipdata = (unsigned short*)bip_mat->data;

	hyper_mat res = create_hyper_mat(samples,lines,bands,4,bip_mat->interleave);
	
	float* res_data = (float*)res->data;

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < samples; j++)
		{
			for (int k = 0; k < bands; k++)
			{
				res_data[i*samples*bands + j*bands + k] = bipdata[i*samples*bands + j*bands + k] * coefficient[k*bands + j];
			}
		}
	}
	return res;
}

hyper_mat absolute_radiometric_correction(hyper_mat bip_mat, float* coefficient)
{
	int samples = bip_mat->samples;
	int lines = bip_mat->lines;
	int bands = bip_mat->bands;

	float* bipdata = (float*)bip_mat->data;

	hyper_mat res = create_hyper_mat(samples, lines, bands, 4, bip_mat->interleave);

	float* res_data = (float*)res->data;

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < samples; j++)
		{
			for (int k = 0; k < bands; k++)
			{
				res_data[i*samples*bands + j*bands + k] = bipdata[i*samples*bands + j*bands + k] * coefficient[k];
			}
		}
	}
	return res;
}







