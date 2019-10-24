#include "precomp.h"
#include <errno.h>
//*************************************************************  private *****************************************************************

#ifndef MAXLINE
#define MAXLINE 20 //each line no more than 20 words
#endif

// private function purpose to compare 2 char[]
int cmpstr(char temp1[],char temp2[])
{

	if(strlen(temp1)!=strlen(temp2))
		return 0;

	for (int i=0;i<strlen(temp1);i++)
	{
		if(temp1[i]!=temp2[i])
			return 0;
	}
	return 1;
}

//* @param[in]  data_type   data_type of hyper spectral image, data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer.

#if gdal_switch
static int date_type_2_gdal_data_type(const int data_type)
{
	switch (data_type)
	{
		case 1:
			return GDT_Byte;
			break;
		case 2:
			return GDT_Int16;
			break;
		case 3:
			return GDT_Int32;
			break;
		case 4:
			return GDT_Float32;
			break;
		case 5:
			return GDT_Float64;
			break;
		case 12:
			return GDT_UInt16;
			break;
		case 13:
			return GDT_UInt32;
			break;
	}
	return GDT_Unknown;

}
#endif

//*************************************************************  public function  ********************************************************
/**
 * @brief      create a hyper mat.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 **/
hyper_mat create_hyper_mat(const int samples, const int lines, const int bands, const int data_type, const char interleave[])
{
	hyper_mat mat = create_hyper_mat_with_data(samples, lines, bands, data_type, interleave, NULL,NULL);
	return mat;
}

/**
 * @brief      create a hyper mat.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil/bsq/bip.
 * @param[in]  data        pointer of image data.
 * @retvall     hyper_mat   hyper mat.
 **/
hyper_mat create_hyper_mat_with_data(const int samples, const int lines, const int bands, const int data_type, const char interleave[], void* data,float* wavelength)
{
	_assert(samples > 0, "the samples of hyper mat must be greater than zero.");
	_assert(lines > 0, "the lines of hyper mat must be greater than zero.");
	_assert(bands > 0, "the bands of hyper mat must be greater than zero.");

	hyper_mat mat;

	int memneeded = sizeof(HyperMat);
	int elem_size = get_elemsize(data_type);

	if (data == NULL)
	{
		int mat_data_size = samples * lines * bands * elem_size;
		memneeded += mat_data_size + ALLOC_BYTE_ALIGNMENT;
	}

	mat = (hyper_mat)malloc(sizeof(char) * memneeded);
	_assert(mat != NULL, "fail to allocate memory for hyper mat");

	if (data == NULL)
	{
		uintptr_t address = (uintptr_t)mat + sizeof(hyper_mat);
		BYTE_ALIGNMENT(address, ALLOC_BYTE_ALIGNMENT);
		memset((void*)address, 0, samples * lines * bands * elem_size);
		mat->data = (void*)address;
	}
	else
		mat->data = data;

	mat->samples = samples;
	mat->lines = lines;
	mat->bands = bands;
	mat->data_type = data_type;
	mat->interleave[0] = interleave[0];
	mat->interleave[1] = interleave[1];
	mat->interleave[2] = interleave[2];
	mat->interleave[3] = '\0';
	mat->wavelength = wavelength;
	return mat;
}

/**
 * @brief      read the hyper spectral image.
 * @param[in]  image_path  hyper spectral image path.
 * @retval      hyper_mat   hyper mat.
 **/
hyper_mat hmread_with_hdr(const char* image_path,const char* hdr_path)
{
	_assert(image_path != NULL, "image path or hdr path can not be NULL");

	FILE* image_fp = NULL;
	FILE* hdr_fp = NULL;

	image_fp = fopen( image_path, "r");
	hdr_fp = fopen(hdr_path, "r");

	int samples, lines, bands, data_type;
	char interleave[3];

	float* wavelength = NULL;

	if (image_fp == NULL || hdr_fp == NULL)
	{
		printf("can not open file\n");
		return 0;
	}
	else
		readhdr(hdr_fp, &samples, &lines,&bands, &data_type, interleave, wavelength);

	int elem_size = get_elemsize(data_type);
	int data_size = samples * lines * bands;

	void* data = (void *)malloc(data_size * elem_size);

	fread(data, elem_size, data_size, image_fp);
	fclose(image_fp);
	fclose(hdr_fp);

	hyper_mat mat = create_hyper_mat_with_data(samples, lines, bands, data_type, interleave, data,wavelength);

#if _DEBUG 
	hyper_mat_showinfo(mat);
#endif

	return mat;
}

/**
 * @brief      read the hyper spectral image with size.
 * @param[in]  image_path  hyper spectral image path.
 * @param[in]  samples     hyper spectral image samples.
 * @param[in]  lines       hyper spectral image lines.
 * @param[in]  bands       hyper spectral image bands.
 * @param[in]  data_type   hyper spectral image data_type.
 * @param[in]  interleave  bsq,bil,bip.
 **/
hyper_mat hmread_with_size(const char* image_path, int samples, int lines, int bands, int data_type, char* interleave)
{
	_assert(image_path != NULL, "image path or hdr path can not be NULL");
	_assert(samples >0 && lines>0 && bands>0, "image size must >0 ");

	FILE* image_fp = NULL;
	image_fp = fopen( image_path, "r");

	if (image_fp == NULL)
	{
		printf("can not open file\n");
		return 0;
	}

	int elem_size = get_elemsize(data_type);
	int data_size = samples * lines * bands;

	void* data = (void *)malloc(data_size * elem_size);

	fread(data, elem_size, data_size, image_fp);
	fclose(image_fp);

	hyper_mat mat = create_hyper_mat_with_data(samples, lines, bands, data_type, interleave, data,NULL);

	return mat;
}
/**
 * @brief      write the hyper spectral image.
 * @param[in]  image_path  hyper spectral image path.
 * @param[in]  hyper_mat   hyper mat.
 **/
void hmwrite(const char* image_path, hyper_mat mat)
{
	_assert(image_path != NULL && mat != NULL, "image_path & mat could not be NULL");
	int elemsize = get_elemsize(mat->data_type);
	int samples = mat->samples;
	int lines = mat->lines;
	int bands = mat->bands;

	float* t = (float*)mat->data;

#if gdal_switch
	GDALAllRegister();
	GDALDatasetH  dst;
	GDALDriverH hDriver = GDALGetDriverByName("ENVI");	
	int DT = date_type_2_gdal_data_type(mat->data_type);
	dst = GDALCreate(hDriver,image_path, samples, lines, bands, DT, NULL);
	GDALRasterBandH hBand;
	for(int i=1;i<=bands;i++)
	{
		hBand = GDALGetRasterBand(dst,i);	
		int tmp = GDALRasterIO(hBand, GF_Write, 0, 0, samples, lines, t+(i-1)*samples*lines, samples, lines, DT, 0, 0);	
	}
	GDALClose(dst);
#else

	FILE* image_fp;
	image_fp = fopen( image_path, "w");
	_assert(image_fp == NULL, "can not open files");
	fwrite(mat->data, elemsize, samples * lines * bands, image_fp);
	writehdr(image_path, samples, lines, bands, mat->data_type, mat->interleave,mat->wavelength);
	fclose(image_fp);
#endif
}

/**
 * @brief      read the HDR to get size and data type.
 * @param[in]  hdr_fp      hdr file.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 **/
void readhdr(FILE* hdr_fp, int* samples, int* lines, int* bands, int* data_type, char interleave[],float* wavelength)
{
	_assert(hdr_fp != NULL, "can not open hdr file");

	char line[MAXLINE];
	char item[MAXLINE];

	int sampletemp = 0, linetemp = 0, bandtemp = 0, datatypetemp = 0;

	while (fgets(line, MAXLINE, hdr_fp) != 0)
	{   
		sscanf(line, "%[^=]", item);

		if (cmpstr(item, "samples") == 1)
			sscanf(line, "%*[^=]=%d",&sampletemp);

		else if (cmpstr(item, "lines") == 1)
			sscanf(line, "%*[^=]=%d",&linetemp);

		else if (cmpstr(item, "bands") == 1)
			sscanf(line, "%*[^=]=%d", &bandtemp);
		else if (cmpstr(item, "data") > 0)
			sscanf(line, "%*[^=]=%d", &datatypetemp);
		else if (cmpstr(item, "interleave") > 0)
			sscanf(line, "%*[^=]=%s", interleave);

	}

	*samples = sampletemp ;
	*lines = linetemp;
	*bands = bandtemp;
	*data_type = datatypetemp;
}

/**
 * @brief      write the HDR file.
 * @param[in]  img_path    image file path.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 **/
void writehdr(const char* img_path, int samples, int lines, int bands, int data_type, const char interleave[],float* wavelength)
{
	const char* t = img_path;
	int len = 0;
	while (*t++ != '\0')
	{
		len++;
	}
	char* hdr_path = (char*)malloc((len + 5)*sizeof(char));
	for (int i = 0; i < len; i++)
		hdr_path[i] = img_path[i];
	hdr_path[len] = '.';
	hdr_path[len + 1] = 'h';
	hdr_path[len + 2] = 'd';
	hdr_path[len + 3] = 'r';
	hdr_path[len + 4] = '\0';
	//todo fix write hdr with bands
	FILE *fp;
	fp = fopen(hdr_path, "w");
	fputs("ENVI\n", fp);
	fputs("samples = ", fp); fprintf(fp, "%d\n", samples);
	fputs("lines = ", fp); fprintf(fp, "%d\n", lines);
	fputs("bands = ", fp); fprintf(fp, "%d\n", bands);
	fputs("data type = ", fp); fprintf(fp, "%d\n", data_type);
	fputs("interleave = ", fp); fprintf(fp, "%s\n", interleave);
	fclose(fp);
}


/**
 * @brief       copy hyper mat.
 * @param[in]   mat         input hyper mat.
 * @retval      hyper_mat   output hyper mat.
 **/
hyper_mat hyper_mat_copy(hyper_mat mat)
{
	_assert(mat!=NULL,"mat could not be NULL");
	int samples = mat->samples;
	int lines = mat->lines;
	int bands = mat->bands;
	int data_type = mat->data_type;
	int elemsize = get_elemsize(data_type);

	char interleave[3];

	interleave[0] = mat->interleave[0];
	interleave[1] = mat->interleave[1];
	interleave[2] = mat->interleave[2];

	hyper_mat dst_mat = create_hyper_mat(samples,lines,bands,data_type,interleave);

	char *dst_data = (char*)dst_mat->data;
	char *src_data = (char*)mat->data;

	memcpy(dst_data,src_data,samples*lines*bands*elemsize);

	return dst_mat;
}

/**
 * @brief      function to show information the hyper mat.
 * @param[in]  mat         hyper mat.
 **/
void hyper_mat_showinfo(hyper_mat mat)
{
	if(mat == NULL)
		printf("mat is NULL");
	else
	{
		printf("mat's samples is %d", mat->samples);
		printf("mat's lines is %d",mat->lines);	
		printf("mat's bands is %d",mat->bands);
		printf("mat's data type is %d",mat->data_type);
		printf("mat's interleave is %c%c%c",mat->interleave[0],mat->interleave[1],mat->interleave[2]);	
	}
}


/**
 * @brief      function to delete the hyper mat.
 * @param[in]  mat         hyper mat.
 **/
void delete_hyper_mat(hyper_mat mat)
{
	_assert(mat != NULL, "already free");
	if ((uintptr_t)mat + ALLOC_BYTE_ALIGNMENT >= (uintptr_t)mat->data)
	{
		free(mat);
		mat = NULL;
	}
	else
	{
		free(mat->data);
		mat->data = NULL;
		free(mat->wavelength);
		mat->wavelength = NULL;
		free(mat);
		mat = NULL;
	}
}




