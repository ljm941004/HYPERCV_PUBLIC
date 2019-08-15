
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
* @brief      function to delete the simple mat.
* @param[in]  mat         simple mat.
**/
void delete_simple_mat(simple_mat mat);
