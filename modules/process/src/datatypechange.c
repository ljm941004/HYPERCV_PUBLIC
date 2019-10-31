/*************************************************************************
	> File Name: datatypechange.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

/**
* @brief      data type change .
* @param[in]  f_mat      float image.
* @retval     dst        int image.
**/
//todo write all brief and fix order data type
hyper_mat hyper_mat_float2int(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float");
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

/**
* @brief      data type change .
* @param[in]  f_mat      float image.
* @retval     dst        char image.
**/
hyper_mat hyper_mat_float2char(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float")
		int samples = f_mat->samples;
	int lines = f_mat->lines;
	int bands = f_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,1,f_mat->interleave);

	char* data = dst->data;
	float* fdata = f_mat->data;
	int tmp = 0;
	int datasize = samples*lines*bands;
	for(int i=0;i<datasize;i++)
	{
		tmp = HYPERCV_ROUND(fdata[i]);

		if(tmp>127)
			data[i] = 128;
		else if(tmp<-127)
			data[i] = -127;
		else
			data[i] = tmp;

	}
	return dst;
}

/**
* @brief      data type change .
* @param[in]  f_mat      float image.
* @retval     dst        short image.
**/
hyper_mat hyper_mat_float2short(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float");
    int samples = f_mat->samples;
	int lines = f_mat->lines;
	int bands = f_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,2,f_mat->interleave);

	short* data = dst->data;
	float* fdata = f_mat->data;
	int tmp = 0;
	int datasize = samples*lines*bands;
	for(int i=0;i<datasize;i++)
		data[i] =(short)HYPERCV_ROUND(fdata[i]);
	return dst;
}

/**
 * @brief      data type change .
 * @param[in]  f_mat      float image.
 * @retval     dst        unsigned short image.
 **/
hyper_mat hyper_mat_float2ushort(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float");
	int samples = f_mat->samples;
	int lines = f_mat->lines;
	int bands = f_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,12,f_mat->interleave);

	unsigned short* data = dst->data;
	float* fdata = f_mat->data;
	int tmp = 0;
	int datasize = samples*lines*bands;
	for(int i=0;i<datasize;i++)
	{
		tmp = HYPERCV_ROUND(fdata[i]);
		if(tmp<0)
			data[i] =0;
		else
			data[i] = tmp;
	}
	return dst;
}

/**
 * @brief      data type change .
 * @param[in]  f_mat      float image.
 * @retval     dst        unsigned char image.
 **/
hyper_mat hyper_mat_float2uchar(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float");
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

/**
 * @brief      data type change .
 * @param[in]  f_mat      float image.
 * @retval     dst        unsigned int image.
 **/
hyper_mat hyper_mat_float2uint(hyper_mat f_mat)
{
	_assert(f_mat->data_type == 4,"intput mat datatype == float");
	int samples = f_mat->samples;
	int lines = f_mat->lines;
	int bands = f_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,13,f_mat->interleave);

	unsigned int * data = dst->data;
	float* fdata = f_mat->data;
	int tmp = 0;
	int datasize = samples*lines*bands;
	for(int i=0;i<datasize;i++)
	{
		tmp = HYPERCV_ROUND(fdata[i]);

		if(tmp>4294967295)
			data[i] =4294967295;
		else if(tmp<0)
			data[i] = 0;
		else
			data[i] = tmp;

	}
	return dst;
}


/**
 * @brief      data type change .
 * @param[in]  f_mat      unsined short image.
 * @retval     dst        float image.
 **/
hyper_mat hyper_mat_ushort2float(hyper_mat us_mat)
{
	_assert(us_mat->data_type == 12,"intput mat datatype == unsigned short");
	int samples = us_mat->samples;
	int lines = us_mat->lines;
	int bands = us_mat->bands;

	hyper_mat dst = create_hyper_mat(samples,lines,bands,4,us_mat->interleave);

	unsigned short* usdata = us_mat->data;
	float* fdata = dst->data;
	int tmp = 0;
	int datasize = samples*lines*bands;
	for(int i=0;i<datasize;i++)
	{
	
			fdata[i] = usdata[i]*1.0;
	}
	return dst;
}



float hypercv_atof(const char *str)
{
	const char *p = str;
	int sign = 1;
	while(*p == ' ')++p;
	if(*p == '-')
	{
		sign = -1;
		++p;
	}
	
	else if (*p == '+')
		++p;
	int hasDot = 0,hasE = 0;
	float integerPart = 0.0,decimalPart = 0.0;

	for (; *p; ++p)
	{
		if (isdigit(*p)) 
			integerPart = 10 * integerPart + *p - '0';
		else if (*p == '.')
		{
			hasDot = 1;
			p++;
			break;
		}
		else if (*p == 'e' || *p == 'E')
		{
			hasE = 1;
			p++;
			break;
		}
		else
			return integerPart;
	}

	int decimalDigits = 1;
	int exponential = 0;    

	for (; *p; p++)
	{
		if (hasDot && isdigit(*p))
			decimalPart += (*p - '0') / pow(10, decimalDigits++);
		else if (hasDot && (*p == 'e' || *p == 'E'))
		{
			integerPart += decimalPart;
			decimalPart = 0.0;
			hasE = 1;
			++p;
			break;
		}
		else if (hasE && isdigit(*p))
			exponential = 10 * exponential + *p - '0';
		else break;
	}

	if (hasE && hasDot)
		for (; *p; p++)
			if (isdigit(*p))
				exponential = 10 * exponential + *p - '0';
	return sign * (integerPart * pow(10, exponential) + decimalPart);

}

char* hypercv_ftoa(float* wavelength)
{




}














