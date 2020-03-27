/*************************************************************************
	> File Name: algorithm/test/testdft.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
#ifndef opencv_switch
#define opencv_switch 0 
#endif


using namespace std;

static simple_mat mat;
static simple_mat dst_mat;

template<typename type>
static void hypercv_test_setup(int rows, int cols, int data_type, int channels)
{
  	mat = create_simple_mat(rows, cols, data_type, channels);
	hypercv_dataInit<type>((type*)mat->data,cols,rows,channels);
	dst_mat = create_simple_mat(rows, cols, data_type, channels);
}


//dubug todo 
void test_hypercv_dft()
{
  // hypercv_test_setup<unsigned char>(100,100,1,3);

	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	simple_mat gmat = sm_rgb2gray(mat,0);

	int m = getOptimalDFTSize(gmat->rows);
	int n = getOptimalDFTSize(gmat->cols);

	simple_mat padded = hypercv_copy_make_border(gmat,0,m-gmat->rows,0,n-gmat->cols,BORDER_CONSTANT,0);

	smwrite_bmp("padded.bmp",padded);
///	
	simple_mat remat = create_simple_mat(padded->rows,padded->cols,4,1);
	simple_mat immat = create_simple_mat(padded->rows,padded->cols,4,1);
	hypercv_dft(padded,remat,immat);

	simple_mat mag = simple_mat_copy(remat);
	hypercv_magnitude(remat, immat, mag);

	hypercv_normalize(mag,mag,0,255,NORM_MINMAX);

	smwrite_bmp("TEST.bmp",mag);

}
TEST(ALGORITHM,DFT)
{
	test_hypercv_dft();
}
