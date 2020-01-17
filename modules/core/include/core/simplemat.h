typedef struct 
{	
	int   rows;
	int   cols;
	int   data_type;
	int   channels;
	int   elem_size;
	void* data;
}SIMPLE_MAT;

typedef SIMPLE_MAT* simple_mat;

typedef struct BmpFileHeader
{
	unsigned short	bfType;
	unsigned int	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned int	bfOffBits;
}__attribute__((packed)) BmpFileHeader;
 
/*bmp info header*/
typedef struct BmpInfoHeader
{
	unsigned int	biSize;
	int				biWidth;
	int				biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	int				biXPelsPerMeter;
	int 			biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
}__attribute__((packed)) BmpInfoHeader;
 
//we won't use it while BitCount=24
typedef struct tagRGBQUAD
{
	unsigned char	rgbBlue;
	unsigned char	rgbGreen;
	unsigned char	rgbRed;
	unsigned char	rgbReserved;
}RGBQUAD;
	
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RGB_data;

/**
 * @brief	constructor for matrix headers pointing to user-allocated data
 * @param[in]  rows			Number of rows in a 2D array.
 * @param[in]  cols			Number of columns in a 2D array.
 * @param[in]  data_type	same as hyper mat data type.
 * @param[in]  channels 	channels of 2d image.
 * @retval      simple_mat   2D mat. 
 **/
simple_mat create_simple_mat(int rows, int cols, int date_type, int channels);

/**
 * @brief	constructor for matrix headers pointing to user-allocated data
 * @param[in]  rows			Number of rows in a 2D array.
 * @param[in]  cols			Number of columns in a 2D array.
 * @param[in]  data_type	same as hyper mat data type.
 * @param[in]  channels 	channels of image.
 * @param[in]  data			Pointer to the user data.
 * @retval     simple_mat   2D mat. 
 **/
simple_mat create_simple_mat_with_data(int rows, int cols, int data_type, int channels, void* data);

/**
* @brief      read the 2D image.
* @param[in]  image_path  hyper spectral image path.
* @retval      simple_mat   2D mat. 
**/
simple_mat smread(const char * image_path, int rows, int cols, int data_type, int channels);

/**
 * @brief      copy simple mat.
 * @param[in]  mat  input simple mat.
 * @retval     simple_mat. 
 **/
simple_mat simple_mat_copy(simple_mat mat);

/**
* @brief      function to save the simple mat.
* @param[in]  path        save path.
* @param[in]  mat         simple mat.
**/
void sm_save_2_bmp(const char* path, simple_mat mat);

/**
* @brief      function to read a bmp image into simple mat.
* @param[in]  bmpName     bmp image path.
* @retval     simple_mat. 
**/
simple_mat smread_bmp(const char *bmpName);

/**
* @brief      function to save the simple mat into bmp image.
* @param[in]  bmpName     save path.
* @param[in]  mat         simple mat.
**/
void smwrite_bmp(const char *bmpName, simple_mat src_mat);

/**
* @brief      function calculate mean value of simple mat.
* @param[in]  mat         simple mat.
* @retval     mean value. 
**/
float simple_mat_mean(simple_mat mat);

/**
* @brief      function calculate variance of simple mat.
* @param[in]  mat         simple mat.
* @retval     variance. 
**/
float simple_mat_variance(simple_mat mat);

/**
* @brief      function calculate contrast ratio of simple mat.
* @param[in]  mat         simple mat.
* @retval     variance. 
**/
float simple_mat_contrast_ratio(simple_mat mat);

/**
* @brief      function to statist grayscale.
* @param[in]  mat              simple mat.
* @param[in]  gray_statist     grayscale.
**/
void simple_mat_grayscale_statistics(simple_mat mat , int* gray_statist);

/**
* @brief      function calculate entropy of simple mat.
* @param[in]  mat         simple mat.
* @retval     entropy. 
**/
float simple_mat_entropy(simple_mat mat);

/**
* @brief      function to delete the simple mat.
* @param[in]  mat         simple mat.
**/
void delete_simple_mat(simple_mat mat);

