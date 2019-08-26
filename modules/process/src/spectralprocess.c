#include "precomp.h"

//___________private_math_function_________
float sp_average(float *x, int length)
{
	float sum = 0;
	for (int i = 0; i<length; i++)
		sum += x[i];
	return sum / length;
}

float sp_variance(float* x, int length)
{
	float average = sp_average(x, length);
	float sum = 0;
	for (int i = 0; i<length; i++)
		sum += pow(x[i] - average, 2);
	return sum / length;
}

float sp_standard_deviation(float *x, int length)
{
	float sd = sp_variance(x, length);
	return sqrt(sd);
}

/*
   __________________________________________________________________________________________

   __________________________________________________________________________________________
   */

/**
 * @brief      using known spectrum to match all image. 
 * @param[in]  bip_data    bip image data.
 * @param[in]  spectrum    match spectrum.
 * @param[in]  threshold   threshold of match, default 0.8.
 **/
simple_mat spectrum_SAM_match(hyper_mat bip_mat, float* spectrum, float threshold)
{
	_assert(bip_mat != NULL, "input hyper mat must not be NULL");
	_assert(cmpstr(bip_mat->interleave, "bip") == 1, "hyper mat interleave should be bip");
	_assert(spectrum != NULL, "spectrum must not be NULL");

	int samples = bip_mat->samples;
	int lines = bip_mat->lines;
	int bands = bip_mat->bands;
	int elem_size = get_elemsize(bip_mat->data_type);

	simple_mat match_image = create_simple_mat(lines, samples, 1,1);

	//only use in short datetype
	short* bip;
	char*  smat;

	float* temp = (float*)malloc(sizeof(float)*bands);
	/*
	 * todo
	 for (int i = 0; i < lines; i++)
	 {
	 for (int j = 0; j < samples; j++)
	 {
	 bip = (short*)((char *)bip_mat->data + (i * samples * bands + j * bands) * elem_size);

	 for (int k = 0; k < bands; k++)
	 {
	 float t = (float)(*bip);
	 temp[k] = t;
	 bip++;
	 }

	 float res = spectral_angle_mapper(temp, spectrum, bands);

	 smat = (char*)match_image->data + i*samples + j;
	 if (res >= threshold)
	 *smat = 1;
	 else
	 *smat = 0;
	 }
	 }
	 */
	return match_image;
}

/**
 * @brief      calculate two vector similar.
 * @param[in]  x           vector x.
 * @param[in]  y           vector y.
 * @param[in]  length      length of two vector.
 **/
float spectral_angle_mapper(float * x, float * y, int length)
{
	_assert(x != NULL && y != NULL, "spectral angle mapper input must not be NULL");

	float XY = 0.0, X = 0.0, Y = 0.0;

	float res = 0.0;

	for (int i = 0; i<length; i++)
	{
		XY += abs(*x * *y);
		X += (*x)*(*x);
		Y += (*y)*(*y);
	}

	res = acos(XY / sqrt(X*Y));

	return res;
}

/**
 * @brief      read spectrum from txt file.
 * @param[in]  sp_path     spectrum file path.
 * @param[in]  length      length of spectrum.
 **/
float* read_spectrum_file(const char* sp_path, int length)
{
	FILE *fp;
	fp = fopen(sp_path, "r");

	_assert(fp != NULL, "can not open files");

	float* spectrum = (float*)malloc(length*sizeof(float));

	float* sp = spectrum;

	float temp = 0;

	while (fscanf(fp, "%f", &temp) != EOF)
	{
		*sp = temp;
		sp++;
	}

	fclose(fp);
	return spectrum;
}

/**
 * @brief      calculate two vector similar.
 * @param[in]  x           vector x.
 * @param[in]  y           vector y.
 * @param[in]  length      length of two vector.
 **/
float euclidean_distance(float * x, float * y, int length)
{
	float temp = 0;

	for (int i = 0; i<length; i++)
		temp += (x[i] - y[i])*(x[i] - y[i]);

	temp = sqrt(temp);

	return temp;
}

/**
 * @brief      calculate a mean mat of hypermat.
 * @param[in]  mat       input hypermat bip mat.
 **/
void hyper_mat_mean(hyper_mat bip_mat, simple_mat dst_mat)
{
	_assert(bip_mat != NULL, "input hyper mat must not be NULL");
	_assert(cmpstr(bip_mat->interleave, "bip") == 1, "hyper mat interleave should be bip");
	int samples = bip_mat -> samples;
	int lines = bip_mat -> lines;
	int bands = bip_mat -> bands;
	_assert(samples == dst_mat -> cols&&lines == dst_mat->rows,"dst_mat size == bip_mat size");
	_assert(dst_mat->data_type == 4,"simple mat datatype ==4");
//todo other data type
	float* src_data = (float*)bip_mat->data;
	float* dst_data = (float*)dst_mat->data;

	for(int i=0;i<lines;i++)
	{
		for(int j=0;j<samples;j++)
		{
			float* t = src_data + i*samples*bands+j*bands;
			dst_data[i*dst_mat->cols+j]=sp_average(t,bands);		
		}
	}
}

/**
 * @brief      hypermat data reverse.
 * @param[in]  src mat       input hypermat bsq mat.
 * @param[in]  dst mat       revese hypermat bsq mat.
 **/
void hyper_mat_reverse(hyper_mat src_mat, hyper_mat dst_mat)
{
	_assert(src_mat != NULL, "input hyper mat must not be NULL");
	_assert(cmpstr(src_mat->interleave, "bsq") == 1, "hyper mat interleave should be bsq");
	int s_samples = src_mat->samples;
	int d_samples = dst_mat->samples;
	int s_lines = src_mat->lines;
	int d_lines = dst_mat->lines;
	int bands = src_mat->bands;
	_assert(s_samples == d_lines && s_lines == d_samples&& bands == dst_mat->bands,"size must equal");
	char* src =(char*)src_mat->data;
	char* dst =(char*)dst_mat->data;
	int elemsize = get_elemsize(src_mat ->data_type);
	for(int k=0;k<bands;k++)
		for(int i=0;i<d_lines;i++)
			for(int j=0;j<d_samples;j++)
				for(int t=0;t<elemsize;t++)
				dst[k*d_samples*d_lines*elemsize+i*d_samples*elemsize+j*elemsize+t] = src[k*s_samples*s_lines*elemsize+j*s_samples*elemsize+i*elemsize+t];
}
