/*************************************************************************
	> File Name: algorithm/test/testdft.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

using namespace std;

void test_hypercv_dft()
{
	simple_mat mat = smread_bmp("/home/ljm/test.bmp");
    simple_mat gmat = sm_rgb2gray(mat,0);
	simple_mat remat = create_simple_mat(gmat->rows,gmat->cols,4,1);
	simple_mat immat = create_simple_mat(gmat->rows,gmat->cols,4,1);

	hypercv_dft(gmat,remat,immat);

	simple_mat re_mat = simple_mat_float2uchar(remat);
	simple_mat im_mat = simple_mat_float2uchar(immat);

	smwrite_bmp("remat.bmp",re_mat);
	smwrite_bmp("immat.bmp",im_mat);

}
TEST(ALGORITHM,DFT)
{
	test_hypercv_dft();
}
