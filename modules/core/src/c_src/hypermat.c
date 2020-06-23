/*************************************************************************
	> File Name: hypermat.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年01月08日 星期三 22时35分36秒
 ************************************************************************/
#include "precomp.h"

#ifndef MAXLINE
#define MAXLINE 10000 //each line no more than 10000 words
#endif

#ifndef MAXWAVECHAR
#define MAXWAVECHAR 20
#endif

//*************************************************************
//                       private                              * 
//*************************************************************

// function purpose to compare 2 char[]
int cmpstr(char temp1[],char temp2[])
{
	int len = strlen(temp1)<=strlen(temp2)? strlen(temp1):strlen(temp2);

	if(strlen(temp1) == strlen(temp2) && len == 0)
		return 1;

	for(int i=0; i<len; i++)
		if(temp1[i] != temp2[i])
			return 0;

	return 1; 

}

// private function purpose to read wavelength from hdr file
// default wavelength charlength < 12
static void read_wavelength(char* w, float* wavelength, int bands)
{
	char* tmp = (char*)malloc(MAXWAVECHAR*sizeof(char));
	for(int i=0;i<MAXWAVECHAR;i++)
		tmp[i]=' ';
	int t = 0;
	int n = 0;
	for (int i=0;i<strlen(w);i++)
	{
		if(w[i]!=','&&w[i]!='}')
			tmp[t++] = w[i];
		else
		{
			wavelength[n++] = atof(tmp);
			t=0;
			for(int j=0;j<MAXWAVECHAR;j++)
				tmp[j]=' ';
		}
		if(w[i]=='}'||n==bands)
			break;
	}
	free(tmp);
	tmp=NULL;
}


//data_type   data_type of hyper spectral image, data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer.

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


//************************************************************* 
//                   public function 
//*************************************************************

/**
 * @brief      read the HDR to get size and data type.
 * @param[in]  hdr_fp      hdr file.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 **/
void readhdr(FILE* hdr_fp, int* samples, int* lines, int* bands, int* data_type, char* interleave, float** wavelength)
{
	hypercv_assert(hdr_fp != NULL, "can not open hdr file");

	char line[MAXLINE];
	char item[MAXLINE];

	char it[4];

	int sampletemp = 0, linetemp = 0, bandtemp = 0, datatypetemp = 0;

	while (fgets(line, MAXLINE, hdr_fp) != 0)
	{   
		sscanf(line, "%[^=]", item);

		if (cmpstr(item, "samples") == 1)
		{
			sscanf(line, "%*[^=]=%d",&sampletemp);
			*samples = sampletemp ;
		}
		else if (cmpstr(item, "lines") == 1)
		{
			sscanf(line, "%*[^=]=%d",&linetemp);
			*lines = linetemp;
		}
		else if (cmpstr(item, "bands") == 1)
		{
			sscanf(line, "%*[^=]=%d", &bandtemp);
			*bands = bandtemp;
		}
		else if (cmpstr(item, "data") == 1)
		{
			sscanf(line, "%*[^=]=%d", &datatypetemp);
			*data_type = datatypetemp;
		}
		else if (cmpstr(item, "interleave") == 1)
		{
			sscanf(line, "%*[^=]=%c%c%c%c", &it[0],&it[1],&it[2],&it[3]);
			for(int i=0;i<4;i++)
			{
				if(it[i]!=' ')
					*interleave++ = it[i];
			}
		}
		else if (cmpstr(line,"wavelength = {")==1)
		{	
			char* w = (char*)malloc(MAXWAVECHAR * bandtemp*sizeof(char));
			char* t_w = w;

			while (strchr(line, '}') == NULL&&fgets(line, MAXLINE, hdr_fp) != 0)
			{
				for (int i = 0; i < strlen(line); i++)
				{
					if (line[i] != '\n')
						*t_w++ = line[i];
				}
			}
			float* wave = (float*)malloc((bandtemp)*sizeof(float));
			read_wavelength(w, wave, bandtemp);
			*wavelength = wave;
			free(w); w = NULL;
		}
	}
}

/**
 * @brief      create a hyper mat.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 **/
hyper_mat create_hyper_mat(const int samples, const int lines, const int bands, const int data_type, const char* interleave)
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
 * @param[in]  wavelength  wavelength of each bands.
 * @retvall    hyper_mat   hyper mat.
 **/
hyper_mat create_hyper_mat_with_data(const int samples, const int lines, const int bands, const int data_type, const char* interleave, void* data, float* wavelength)
{
	hypercv_assert(samples > 0, "the samples of hyper mat must be greater than zero.");
	hypercv_assert(lines > 0, "the lines of hyper mat must be greater than zero.");
	hypercv_assert(bands > 0, "the bands of hyper mat must be greater than zero.");

	hyper_mat mat;

	long int  memneeded = sizeof(HyperMat);
	int elem_size = get_elemsize(data_type);
    
	long int mat_data_size = samples * lines * bands * elem_size;
	int wave_data_size = bands * sizeof(float);

	memneeded += mat_data_size + ALLOC_BYTE_ALIGNMENT;
	memneeded += wave_data_size + ALLOC_BYTE_ALIGNMENT;

	mat = (hyper_mat)malloc(sizeof(char) * memneeded);
	hypercv_assert(mat != NULL, "fail to allocate memory for hyper mat");

	uintptr_t address = (uintptr_t)mat + sizeof(HyperMat);
	BYTE_ALIGNMENT(address, ALLOC_BYTE_ALIGNMENT);
	memset((void*)address, 0, mat_data_size);
	mat->data = (void*)address;
	
	address += mat_data_size;
	BYTE_ALIGNMENT(address, ALLOC_BYTE_ALIGNMENT);
	memset((void*)address, 0, wave_data_size);
	mat->wavelength = (float*)address;
	
	if(data!=NULL)
		memcpy(mat->data, data, mat_data_size);

	if(wavelength != NULL)
		memcpy(mat->wavelength, wavelength, wave_data_size);

	mat->samples = samples;
	mat->lines = lines;
	mat->bands = bands;
	mat->data_type = data_type;
	mat->interleave[0] = interleave[0];
	mat->interleave[1] = interleave[1];
	mat->interleave[2] = interleave[2];

	return mat;
}


/**
 * @brief      read the hyper spectral image.
 * @param[in]  image_path  hyper spectral image path.
 * @retval     hyper_mat   hyper mat.
 **/
hyper_mat hmread_with_hdr(const char* image_path,const char* hdr_path)
{
	hypercv_assert(image_path != NULL, "image path or hdr path can not be NULL");
	hypercv_assert(hdr_path != NULL, "image path or hdr path can not be NULL");

	int samples, lines, bands, data_type;
	char* interleave = (char*)malloc(3*sizeof(char));
	float* wavelength = NULL;

	FILE* image_fp = NULL;
	FILE* hdr_fp = NULL;

	image_fp = fopen( image_path, "r");
	hdr_fp = fopen(hdr_path, "r");

	if (image_fp == NULL || hdr_fp == NULL)
	{
		printf("can not open file\n");
		return 0;
	}
	else
		readhdr(hdr_fp, &samples, &lines,&bands, &data_type, interleave, &wavelength);
	
	unsigned int elem_size = get_elemsize(data_type);
	long int data_size = samples * lines * bands;

	void* data = (void *)malloc(data_size * elem_size);
	hypercv_assert(data != NULL, "malloc fail");
	
	fread(data, elem_size, data_size, image_fp);
	
	fclose(image_fp);
	fclose(hdr_fp);
	
	hyper_mat mat = create_hyper_mat_with_data(samples, lines, bands, data_type, interleave, data, wavelength);

	free(interleave);
	
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
hyper_mat hmread_with_size(const char* image_path, int samples, int lines, int bands, int data_type, const char* interleave)
{
	hypercv_assert(image_path != NULL, "image path or hdr path can not be NULL");
	hypercv_assert(samples >0 && lines>0 && bands>0, "image size must >0 ");

	FILE* image_fp = NULL;
	image_fp = fopen( image_path, "r");

	if (image_fp == NULL)
	{
		printf("can not open file\n");
		return 0;
	}

	int elem_size = get_elemsize(data_type);
	long int data_size = samples * lines * bands;

	void* data = (void *)malloc(data_size * elem_size);

	fread(data, elem_size, data_size, image_fp);
	fclose(image_fp);

	float* wavelength = (float*)malloc(bands*sizeof(float));

	hyper_mat mat = create_hyper_mat_with_data(samples, lines, bands, data_type, interleave, data, wavelength);

	return mat;
}

/**
 * @brief      write the hyper spectral image.
 * @param[in]  image_path  hyper spectral image path.
 * @param[in]  hyper_mat   hyper mat.
 **/
void hmsave(const char* image_path, hyper_mat mat)
{
	hypercv_assert(image_path != NULL && mat != NULL, "image_path & mat could not be NULL");
	int elemsize = get_elemsize(mat->data_type);
	int samples = mat->samples;
	int lines = mat->lines;
	int bands = mat->bands;

#if gdal_switch

	GDALAllRegister();
	GDALDatasetH  dst;
	GDALDriverH hDriver = GDALGetDriverByName("ENVI");	
	int DT = date_type_2_gdal_data_type(mat->data_type);
	
	char** papszOptions = NULL;
	dst = GDALCreate(hDriver,image_path, samples, lines, bands, DT, papszOptions);
	
	GDALRasterBandH hBand;
	for(int i=1;i<=bands;i++)
	{
		hBand = GDALGetRasterBand(dst,i);	
		int tmp = GDALRasterIO(hBand, GF_Write, 0, 0, samples, lines, (char*)mat->data+(i-1)*samples*lines*elemsize, samples, lines, DT, 0, 0);	
	}
	GDALClose(dst);

	writehdr(image_path, samples, lines, bands, mat->data_type, mat->interleave,mat->wavelength);
#else

	FILE* image_fp;
	image_fp = fopen(image_path, "wb");
	hypercv_assert(image_fp != NULL, "can not open files");
	fwrite(mat->data, elemsize, samples * lines * bands, image_fp);
	writehdr(image_path, samples, lines, bands, mat->data_type, mat->interleave,mat->wavelength);
	fclose(image_fp);

#endif
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
void writehdr(const char* img_path, int samples, int lines, int bands, int data_type, const char* interleave, float* wavelength)
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

	FILE *fp;
	fp = fopen(hdr_path, "w");

	fputs("ENVI\n", fp);
	fputs("samples = ", fp); fprintf(fp, "%d\n", samples);
	fputs("lines = ", fp); fprintf(fp, "%d\n", lines);
	fputs("bands = ", fp); fprintf(fp, "%d\n", bands);
	fputs("data type = ", fp); fprintf(fp, "%d\n", data_type);

	char* it = (char*)malloc(4*sizeof(char));
	for(int i=0;i<3;i++)
		it[i] = interleave[i];
	it[3] = '\0';

	fputs("interleave = ", fp); fprintf(fp, "%s\n", it);

	if(wavelength!=NULL)
	{
		fputs("wavelength = { \n", fp); 
		for(int i=0;i<bands-1;i++)
			fprintf(fp,"%f,",wavelength[i]);
		fprintf(fp,"%f}",wavelength[bands-1]);
	}
	else 
	{
		fputs("wavelength = unknown \n",fp);
	}
	fclose(fp);
}


/**
 * @brief       copy hyper mat.
 * @param[in]   mat         input hyper mat.
 * @retval      hyper_mat   output hyper mat.
 **/
hyper_mat hyper_mat_copy(hyper_mat mat)
{
	if(mat!=NULL)
		return NULL;

	int samples   = mat->samples;
	int lines     = mat->lines;
	int bands     = mat->bands;
	int data_type = mat->data_type;
	int elemsize  = get_elemsize(data_type);

	hyper_mat dst_mat = create_hyper_mat_with_data(samples, lines, bands, data_type, mat->interleave, mat->data, mat->wavelength);

	return dst_mat;
}

/**
 * @brief       copy hyper mat.
 * @param[in]   hyper_mat   input hyper mat.
 * @param[in]   hyper_mat   output hyper mat.
 **/
void hyper_mat_copy_to(hyper_mat src_mat, hyper_mat dst_mat)
{
	hypercv_assert(src_mat!=NULL && dst_mat!=NULL,"INPUT MAT CAN NOT BE NULL");

	int samples   = src_mat -> samples;
	int lines     = src_mat -> lines;
	int bands     = src_mat -> bands;
	int data_type = src_mat->data_type;
	int elemsize  = get_elemsize(data_type);

	hypercv_assert(dst_mat->samples == samples && dst_mat->lines == lines && dst_mat->bands == bands && data_type == dst_mat->data_type,"src_mat size == dst_mat size");

	char* src_data = (char*)src_mat->data;
	char* dst_data = (char*)dst_mat->data;

	memcpy(dst_data, src_data, samples*lines*bands*elemsize);
	hyper_mat_copy_wavelength(src_mat, dst_mat);

	for(int i=0;i<3;i++)
		dst_mat->interleave[i] = src_mat->interleave[i];
}

/**
 * @brief       copy hyper mat wavelength.
 * @param[in]   src         input hyper mat.
 * @param[in]   dst         input hyper mat.
 **/
void hyper_mat_copy_wavelength(hyper_mat src, hyper_mat dst)
{

	hypercv_assert(src!=NULL && dst!=NULL, "mat could not be NULL");
	hypercv_assert(src->bands == dst->bands, "src mat bands == dst mat bands");

	if(src->wavelength == NULL)
		return;

	float* src_wavelength = (float*)src->wavelength;
	float* dst_wavelength = (float*)dst->wavelength;
	
	int bands = src->bands;

	memcpy(dst_wavelength, src_wavelength, bands*sizeof(float));
}

/**
 * @brief      function to show information the hyper mat.
 * @param[in]  mat         hyper mat.
 **/
void hyper_mat_showinfo(hyper_mat mat)
{
	if(mat == NULL)
		printf("mat is NULL\n");
	else
	{
		printf("mat's samples is %d\n", mat->samples);
		printf("mat's lines is %d\n",mat->lines);	
		printf("mat's bands is %d\n",mat->bands);
		printf("mat's data type is %d\n",mat->data_type);
		printf("mat's interleave is %c%c%c\n",mat->interleave[0],mat->interleave[1],mat->interleave[2]);	
		if(mat->wavelength !=NULL)
		{
			printf("mat's wavelength is\n");
			for(int i=0;i<mat->bands;i++)
			{
				printf("%f,",((float*)mat->wavelength)[i]);
			}
		}
	}
}

/**
 * @brief      function to return if mat is empty.
 * @param[in]  mat         hyper mat.
 * @retval     if empty. 
 **/
int hyper_mat_empty(hyper_mat mat)
{
	if(mat == NULL)
		return 1;

	return 0;
}

/**
 * @brief      function to delete the hyper mat.
 * @param[in]  mat         hyper mat.
 **/
void delete_hyper_mat(hyper_mat mat)
{
	if(mat == NULL)
		return;

	free(mat);
	mat = NULL;
}

