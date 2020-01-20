
/**
 * @brief      the definition of hyper mat.
 * @param[in]  samples     samples of hyper spectral image.
 * @param[in]  lines       lines of hyper spectral image.
 * @param[in]  bands       bands of hyper spectral image.
 * @param[in]  data_type   data_type of hyper spectral image, data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer.
 * @param[in]  interleave  interleave of hyper spectral image,such as bil\bsq\bip.
 * @param[in]  data        data pointer of hyper spectral image.
 * @param[in]  wavelength  hyper spectral image wavelength pointer.
 **/
typedef struct  
{
	int    samples;
	int    lines;
	int    bands;
	int    data_type;
	char   interleave[3];
	void*  data;
	float* wavelength;
}HyperMat;

typedef HyperMat* hyper_mat;

int cmpstr(char temp1[],char temp2[]);

/**
 * @brief      create a hyper mat.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 **/
hyper_mat create_hyper_mat(const int samples, const int lines, const int bands, const int data_type, const char* interleave);

/**
 * @brief      create a hyper mat.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 * @param[in]  data        pointer of image data.
 * @param[in]  wavelength  pointer of wavelength.
 **/
hyper_mat create_hyper_mat_with_data(const int samples, const int lines, const int bands, const int data_type, const char* interleave, void* data, float* wavelength);

/**
 * @brief      read the hyper spectral image with hdr.
 * @param[in]  image_path  hyper spectral image path.
 * @param[in]  hdr_path    hdr file path.
 **/
hyper_mat hmread_with_hdr(const char* image_path, const char* hdr_path);

/**
 * @brief      read the hyper spectral image with size.
 * @param[in]  image_path  hyper spectral image path.
 * @param[in]  samples     hyper spectral image samples.
 * @param[in]  lines       hyper spectral image lines.
 * @param[in]  bands       hyper spectral image bands.
 * @param[in]  data_type   hyper spectral image data_type.
 * @param[in]  interleave  bsq,bil,bip.
 **/
hyper_mat hmread_with_size(const char* image_path, int samples, int lines, int bands, int data_type, const char* interleave);

/**
 * @brief      write the hyper spectral image.
 * @param[in]  image_path  hyper spectral image path.
 * @param[in]  hyper_mat   hyper mat.
 **/
void hmwrite(const char* image_path, hyper_mat mat);

/**
 * @brief      read the HDR to get size and data type.
 * @param[in]  hdr_fp      hdr file.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 * @param[in]  wavelength  wavelength pointer.
 **/
void readhdr(FILE* hdr_fp, int* samples, int* lines, int* bands, int* data_type, char* interleave, float** wavelength);

/**
 * @brief      write the HDR file.
 * @param[in]  img_path    image file path.
 * @param[in]  samples     image samples.
 * @param[in]  lines       image lines.
 * @param[in]  bands       image bands.
 * @param[in]  data_type   data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer
 * @param[in]  interleave  bil bsq bip.
 * @param[in]  wavelength  wavelength pointer.
 **/
void writehdr(const char* img_path, int samples, int lines, int bands, int data_type, const char* interleave, float* wavelength);

/**
 * @brief       copy hyper mat.
 * @param[in]   mat         input hyper mat.
 * @retval      hyper_mat   output hyper mat.
 **/
hyper_mat hyper_mat_copy(hyper_mat mat);

/**
* @brief      function to return if mat is empty.
* @param[in]  mat         hyper mat.
* @retval     if empty. 
**/
int hyper_mat_empty(hyper_mat mat);

/**
 * @brief      function to show information the hyper mat.
 * @param[in]  mat         hyper mat.
 **/
void hyper_mat_showinfo(hyper_mat mat);

/**
 * @brief      function to delete the hyper mat.
 * @param[in]  mat         hyper mat.
 **/
void delete_hyper_mat(hyper_mat mat);



