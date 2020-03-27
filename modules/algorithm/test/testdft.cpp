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

void test_hypercv_dft()
{
  // hypercv_test_setup<unsigned char>(100,100,1,3);

	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
	simple_mat gmat = sm_rgb2gray(mat,0);

	simple_mat remat = create_simple_mat(gmat->rows,gmat->cols,4,1);
	simple_mat immat = create_simple_mat(gmat->rows,gmat->cols,4,1);

	dst_mat = create_simple_mat(mat->rows,mat->cols,1,1); 
	simple_mat src_mat = create_simple_mat(mat->rows,mat->cols,1,1); 
	hypercv_dft(gmat,remat,immat);
	hypercv_dft_frespectrum(gmat,dst_mat);
	hypercv_idft(remat,immat,src_mat);

	simple_mat re_mat = simple_mat_float2uchar(remat);

	simple_mat im_mat = simple_mat_float2uchar(immat);

	smwrite_bmp("remat.bmp",re_mat);
	smwrite_bmp("test.bmp",gmat);
	smwrite_bmp("huanyuan.bmp",src_mat);
	smwrite_bmp("immat.bmp",im_mat);
	smwrite_bmp("dst.bmp",dst_mat);

}
TEST(ALGORITHM,DFT)
{
	test_hypercv_dft();
}
