#include "precomp.h"

/**
 * @brief	constructor for matrix headers pointing to user-allocated data
 * @param[in]  rows			Number of rows in a 2D array.
 * @param[in]  cols			Number of columns in a 2D array.
 * @param[in]  data_type	same as hyper mat data type.
 * @param[in]  channels  	channels of simple mat.
 * @retval     simple_mat   2D mat. 
 **/
simple_mat create_simple_mat(int rows, int cols, int date_type, int channels)
{
	simple_mat mat = create_simple_mat_with_data(rows, cols, date_type, channels, NULL);
	return mat;
}

/**
 * @brief	constructor for matrix headers pointing to user-allocated data
 * @param[in]  rows			Number of rows in a 2D array.
 * @param[in]  cols			Number of columns in a 2D array.
 * @param[in]  data_type	same as hyper mat data type.
 * @param[in]  channel   	channels of image.
 * @param[in]  data			Pointer to the user data.
 * @retval      simple_mat   2D mat. 
 **/
simple_mat create_simple_mat_with_data(int rows, int cols, int data_type,int channels, void* data)
{
	_assert(rows > 0 && cols > 0, "the rows and cols of mat must be greater than zero ");

	simple_mat mat;

	int memneeded = sizeof(SIMPLE_MAT);
	int elem_size = get_elemsize(data_type);

	if (data == NULL)
	{
		int data_size = rows * cols * elem_size * channels; 
		memneeded += data_size + ALLOC_BYTE_ALIGNMENT;
	}

	mat = (simple_mat)malloc(sizeof(char) * memneeded);
	_assert(mat != NULL, "failed to allocate memory");

	if(data == NULL)
	{
		uintptr_t address = (uintptr_t)mat + sizeof(SIMPLE_MAT);
		BYTE_ALIGNMENT(address, ALLOC_BYTE_ALIGNMENT);
		memset((void*)address, 0, rows * cols * elem_size);
		mat -> data = (void*)address;
	}
	else
		mat -> data = data;

	mat -> rows            = rows;
	mat -> cols            = cols;
	mat -> data_type       = data_type;
    mat -> channels        = channels;
	mat -> elem_size       = elem_size;

	return mat;
}

/**
 * @brief      read the 2D image.
 * @param[in]  image_path  hyper spectral image path.
 * @retval      simple_mat   2D mat. 
 **/
simple_mat smread(const char * image_path, int rows, int cols, int data_type, int channels)
{
	_assert(image_path != NULL, "image path or hdr path can not be NULL");

	FILE* image_fp;
	image_fp = fopen(image_path, "r");

	_assert(image_fp != NULL, "can not open files");

	int elem_size = get_elemsize(data_type);
	int data_size = rows * cols;
	void* data = (void *)malloc(data_size * elem_size);

	fread(data, elem_size, data_size, image_fp);
	fclose(image_fp);

	simple_mat mat;
	mat = create_simple_mat_with_data(rows, cols, data_type, channels, data);

	return mat;
}

/**
 * @brief      copy simple mat.
 * @param[in]  mat  input simple mat.
 * @retval     simple_mat. 
 **/
simple_mat simple_mat_copy(simple_mat mat)
{
    int rows = mat -> rows;
	int cols = mat -> cols;
	int data_type = mat->data_type;
	int elemsize = get_elemsize(data_type);
	int channels = mat->channels;
	
	simple_mat dst = create_simple_mat(rows,cols,data_type,channels);
	
	char * src_data = (char*)mat->data;
	char * dst_data = (char*)dst->data;
	
	memcpy(dst_data,src_data,rows*cols*elemsize);
	
	return dst;
}


/**
* @brief      function to read a bmp image into simple mat.
* @param[in]  bmpName     bmp image path.
* @retval     simple_mat. 
**/
simple_mat smread_bmp(char *bmpName)
{
	_assert(bmpName!=NULL,"read bmp file name can not be NULL");
	
	FILE *fp = fopen(bmpName, "rb");

	_assert(fp!=NULL,"BMP IMAGE NOT EXIST");

	fseek(fp, sizeof(BmpFileHeader), SEEK_SET);
	BmpInfoHeader head;
	fread(&head, sizeof(BmpInfoHeader), 1, fp);
 
	int bmpWidth = head.biWidth;
	int bmpHeight = head.biHeight;
	int biBitCount = head.biBitCount;
    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	
	if (biBitCount == 8)
	{
		RGBQUAD *pColorTable = (RGBQUAD *)malloc(sizeof(RGBQUAD) * 1024);
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	unsigned char* pBmpBuf = (unsigned char *)malloc(sizeof(unsigned char) * lineByte * bmpHeight);
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	fclose(fp);

	simple_mat res = create_simple_mat_with_data(bmpHeight,bmpWidth,1,3,pBmpBuf);

	return res;
}

/**
* @brief      function to save the simple mat into bmp image.
* @param[in]  bmpName     save path.
* @param[in]  mat         simple mat.
**/
void smwrite_bmp(char *bmpName, simple_mat src_mat)
{
	_assert(bmpName != NULL, "write bmp image path can not be NULL");
	_assert(src_mat != NULL,"save mat can not be null");
	_assert(src_mat->data_type == 1,"save mat only 0-255");

	FILE *fp = fopen(bmpName, "wb");
	_assert(fp != NULL,"save file can not open");
	
	simple_mat mat;
	if(src_mat -> channels == 1)
		mat = sm_gray2rgb(src_mat);
	else 
		mat = src_mat;

	unsigned char* imgBuf = (unsigned char*) mat->data;
	int width = mat -> cols;
	int height = mat -> rows;
	int data_type = mat -> data_type;

	// default 24 ,also can use in byte
	int biBitCount = 24;
 
	int colorTablesize = 0;
	if (biBitCount == 8)
	{
		colorTablesize=1024;
	}
	
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
//   int lineByte = (width * biBitCount + 31) /32 *4;	
	BmpFileHeader fileHead;
	fileHead.bfType=0x4D42;
 
	fileHead.bfSize = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + colorTablesize + lineByte * height;
	
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
 
	fileHead.bfOffBits = 54 + colorTablesize;
 
	fwrite(&fileHead, sizeof(BmpFileHeader), 1, fp);
 
	BmpInfoHeader infoHead;
	infoHead.biBitCount = biBitCount;
	infoHead.biClrImportant = 0;
	infoHead.biClrUsed = 0;
	infoHead.biCompression = 0;
	infoHead.biHeight = height;
	infoHead.biPlanes = 1;
	infoHead.biSize = 40;
	infoHead.biSizeImage = lineByte * height;
	infoHead.biWidth = width;
	infoHead.biXPelsPerMeter = 100;
	infoHead.biYPelsPerMeter = 100;
 
	fwrite(&infoHead, sizeof(BmpInfoHeader), 1, fp);
 
/*	if (biBitCount == 8)
	{
		fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	}
*/
	if(lineByte>width*biBitCount/8)
	{
		unsigned char* tmp = (unsigned char*)malloc(height*lineByte);
		unsigned char* data = tmp ;
		for(int i=0;i<height;i++)
		{
			memcpy(data,imgBuf,width*3);
			imgBuf+=width*3;
			data+=lineByte;
		}
		fwrite(tmp,height*lineByte,1,fp);
		free(tmp);
	}
	else 
		fwrite(imgBuf,height*lineByte, 1, fp);
	
	fclose(fp);

/*	if(mat != src_mat)
	{
		delete_simple_mat(mat);
	}
	*/
}


float simple_mat_mean(simple_mat mat)
{
	_assert(mat!=NULL,"input_mat cannot be NULL");
	_assert(mat->channels == 1,"only use in gray image");
	int rows = mat -> rows;
	int cols = mat -> cols;

	float res = 0.0;

	switch (mat->data_type)
	{
		case 1:
			{
				unsigned char* data = (unsigned char*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res+=data[i];
				break;
			}
		case 2:
		case 12:
			{
				unsigned short* data = (unsigned short*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res+=data[i];
				break;
			}
		case 3:
			{
				unsigned int* data = (unsigned int*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res+=data[i];
				break;
			}
		case 4:
			{
				float* data = (float*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res+=data[i];
				break;
			}
	}
	return res/rows/cols;
}


float simple_mat_variance(simple_mat mat)
{
	_assert(mat != NULL,"input mat cannot be NULL");
	_assert(mat->channels == 1,"only use in gray image");
	int rows = mat->rows;
	int cols = mat->cols;
	float res =0.0;
	float mean = simple_mat_mean(mat);
	switch (mat->data_type)
	{
		case 1:
			{
				unsigned char* data = (unsigned char*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res += pow(mean-data[i],2);
				break;
			}
		case 2:
		case 12:
			{
				unsigned short* data = (unsigned short*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res += pow(mean-data[i],2);
				break;
			}
		case 3:
			{
				unsigned int* data = (unsigned int*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res += pow(mean-data[i],2);
				break;
			}
		case 4:
			{
				float* data = (float*) mat->data;
				for(int i=0;i<rows*cols;i++)
					res += pow(mean-data[i],2);
				break;
			}
	}
	return res/rows/cols;
}


void simple_mat_grayscale_statistics(simple_mat mat , int* gray_statist)
{
	_assert(mat != NULL,"input mat cannot be NULL");
	_assert(mat-> data_type == 1,"only use in unsigned char image");
	_assert(sizeof(gray_statist)==256,"gray array error");

	int rows = mat->rows;
	int cols = mat->cols;
	int channels = mat->channels;

	simple_mat tmp ;

	if(channels != 1)
		tmp = sm_rgb2gray(mat,0);
	else 
		tmp = mat;

	unsigned char* data = (unsigned char*)tmp->data;

	for(int i=0;i<256;i++)
		gray_statist[i] = 0;

	for(int i=0; i<rows*cols; i++)
		gray_statist[data[i]]++;
}


float simple_mat_contrast_ratio(simple_mat mat)
{
	_assert(mat != NULL,"input mat cannot be NULL");
	_assert(mat-> data_type == 1,"only use in unsigned char image");

	int rows = mat->rows;
	int cols = mat->cols;
	int channels = mat->channels;

	simple_mat tmp ;

	if(channels != 1)
		tmp = sm_rgb2gray(mat,0);
	else 
		tmp = mat;

	unsigned char* data = (unsigned char*)tmp->data;

	float res =0.0;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if(j!=0)
				res+=pow(data[i*cols+j]-data[i*cols+j-1],2);
			if(j!=cols-1)
				res+=pow(data[i*cols+j]-data[i*cols+j+1],2);
			if(i!=0)
				res+=pow(data[i*cols+j]-data[(i-1)*cols+j],2);
			if(i!=rows-1)
				res+=pow(data[i*cols+j]-data[(i+1)*cols+j],2);

		}
	}
	
	res = res/(4*(cols-2)*(rows-2)+3*2*(rows-2)+3*2*(cols-2)+2*4);
	return res;
}


float simple_mat_entropy(simple_mat mat)
{
	_assert(mat != NULL,"input mat cannot be NULL");
	_assert(mat-> data_type == 1,"only use in unsigned char image");

	int rows = mat->rows;
	int cols = mat->cols;
	int channels = mat->channels;

	simple_mat tmp ;

	if(channels != 1)
		tmp = sm_rgb2gray(mat,0);
	else 
		tmp = mat;

	unsigned char* data = (unsigned char*)tmp->data;

	float res =0.0;

	int gray_statist[256]={0};
	int * gray_s = gray_statist;

	simple_mat_grayscale_statistics(mat,gray_s);

	for(int i=0;i<256;i++)
	{
		if(gray_statist[i]!=0)
		{
			float temp = (float)gray_statist[i]/rows/cols;
			res = res - temp*(log(temp)/log(2.0));
		}
	}

	return res;
}

/**
 * @brief      function to delete the simple mat.
 * @param[in]  mat         simple mat.
 **/
void delete_simple_mat(simple_mat mat)
{
	if(mat == NULL)
		return;

	if((uintptr_t)mat + ALLOC_BYTE_ALIGNMENT >= (uintptr_t)mat->data)
	{
		free(mat);
		mat = NULL;	
	}
	else	
	{
		free(mat->data);
		mat->data = NULL;
		free(mat);
		mat = NULL;	
	}
}

