/*************************************************************************
	> File Name: datatypechange.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

hyper_mat hyper_mat_float2int(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float")
	int samples = f_mat->samples;
	int lines = f_mat->lines;
	int bands = f_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,3,f_mat->interleave);
	
	int * data = dst->data;
	float* fdata = f_mat->data;
	
	int datasize = samples*lines*bands;

	for(int i=0;i<datasize;i++)
		data[i]=HYPERCV_ROUND(fdata[i]);

	return dst;
}

hyper_mat hyper_mat_float2uchar(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float")
	int samples = f_mat->samples;
	int lines = f_mat->lines;
	int bands = f_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,1,f_mat->interleave);
	
	unsigned char* data = dst->data;
	float* fdata = f_mat->data;
	int tmp = 0;
	int datasize = samples*lines*bands;
	for(int i=0;i<datasize;i++)
	{
		tmp = HYPERCV_ROUND(fdata[i]);
	
		if(tmp>255)
			data[i] = 255;
		else if(tmp<0)
			data[i] = 0;
		else
			data[i] = tmp;

	}
	return dst;
}


hyper_mat hyper_mat_short2float(hyper_mat f_mat)
{
}
