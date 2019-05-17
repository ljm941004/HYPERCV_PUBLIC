#include "stdafx.h"

/**
* @brief      transform bil to bsq.
* @param[in]  bil_mat    bil image.
* @return     bsq_mat    bsq image.
**/
hyper_mat bil2bsq(hyper_mat bil_mat)
{
	_assert(bil_mat != NULL,                "hyper_mat can not be NULL");
	_assert(cmpstr(bil_mat -> interleave,"bil") == 1, "input hyper mat's interleave must be bil");

	int samples   = bil_mat -> samples;
	int lines     = bil_mat -> lines;
	int bands     = bil_mat -> bands;
	int elem_size = get_elem_size(bil_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 's';
	interleave[2] = 'q';
	hyper_mat bsq_mat = create_hyper_mat(samples,lines,bands,bil_mat->data_type,interleave);

	char* bil_data = (char*)bil_mat -> data;
	char* bsq_data = (char*)bsq_mat -> data;

	int bil_index = 0, bsq_index = 0;
	for (int k=0; k<bands; k++)
	{
		for (int i=0; i<lines; i++)
		{
			for (int j=0; j<samples; j++)
			{
				bil_index = (i*samples*bands + k*samples + j)*elem_size;
				bsq_index = (k*samples*lines + i*samples + j)*elem_size;
				for (int t=0; t<elem_size; t++)
					bsq_data[bsq_index + t] = bil_data[bil_index + t];
			}
		}
	}

	return bsq_mat;
}

/**
* @brief      transform bil to bip.
* @param[in]  bil_mat    bil image.
* @return     bip_mat    bip image. 
**/
hyper_mat bil2bip(hyper_mat bil_mat)
{
	_assert(bil_mat != NULL,                "hyper_mat can not be NULL");
	_assert(cmpstr(bil_mat -> interleave,"bil") == 1, "input hyper mat's interleave must be bil");

	int samples   = bil_mat -> samples;
	int lines     = bil_mat -> lines;
	int bands     = bil_mat -> bands;
	int elem_size = get_elem_size(bil_mat->data_type);
	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 'i';
	interleave[2] = 'p';
	hyper_mat bip_mat = create_hyper_mat(samples,lines,bands,bil_mat->data_type,interleave);

	char* bil_data = (char*)bil_mat -> data;
	char* bip_data = (char*)bip_mat -> data;

	int bil_index = 0, bip_index = 0;

	for (int i=0;i<lines; i++)
	{
		for (int j=0;j<samples; j++)
		{
			for (int k=0; k<bands; k++)
			{
				bil_index = (i*samples*bands + k*samples + j)*elem_size;
				bip_index = (i*samples*bands + j*bands + k)*elem_size;
				for (int t=0; t<elem_size; t++)
					bip_data[bip_index + t] = bil_data[bil_index + t];
			}
		}
	}
	return bip_mat;
}

