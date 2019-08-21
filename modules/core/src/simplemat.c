#include "precomp.h"

//______________________ private fuction _______________________

void write_bmp_header(unsigned char* bitmap, int offset, int bytes, int value)
{
	for(int i=0; i<bytes; i++)
		bitmap[offset+i] = (value>>(i<<3)) & 0xFF;
}

unsigned char* convert2bmp(simple_mat mat, int* size)
{
	int width = mat->cols;
	int height = mat->rows;
	unsigned char * data =(unsigned char*) mat->data;
	int bitmap_x = (int)ceil((double)width*3/4)*4;
	unsigned char* bitmap = (unsigned char*)malloc(sizeof(unsigned char)*height*bitmap_x+54);

	bitmap[0] = 'B';
	bitmap[1] = 'M';
	write_bmp_header(bitmap, 2, 4, height*bitmap_x + 54);
	write_bmp_header(bitmap, 0xA, 4, 54);
	write_bmp_header(bitmap, 0XE, 4, 40);
	write_bmp_header(bitmap, 0X12, 4, width);
	write_bmp_header(bitmap, 0X16, 4, height);
    write_bmp_header(bitmap, 0X1A, 2, 1);
	write_bmp_header(bitmap, 0X1C, 2, 24);
	write_bmp_header(bitmap, 0X1E, 4, 0);
	write_bmp_header(bitmap, 0X22, 4, height*bitmap_x);

	for(int i=0x26; i<0x36; i++)
		bitmap[i] = 0;
	int k = 54;
	for(int i=height-1;i>=0;i--)
	{
		int j;
		for(j=0;j<width;j++)
		{
			int index = i*width +j;
			for(int l=0;l<3;l++)
				bitmap[k++] = data[index];
		}
		j*=3;
		while(j<bitmap_x)
		{
			bitmap[k++] = 0;
			j++;
		}
	}

	*size = k;
	return bitmap;
}

//______________________________________________________________




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
		int data_size = rows * cols * elem_size; 
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

void sm_save_2_bmp(const char* path, simple_mat mat)
{
	int size;
	unsigned char* bmp = convert2bmp(mat,&size);
	FILE* fp = fopen(path,"wb+");
	
	fwrite(bmp,1,size,fp);
	fclose(fp);

	free(bmp);
	bmp=NULL;
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
