/*************************************************************************
	> File Name: test/testrotate.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年06月03日 星期三 23时18分50秒
 ************************************************************************/
#include "precomp.h"

using namespace std;
#ifndef TEST_HYPERCV_PERFORMANCE
#define ITERS 1
#else
#define ITES 20
#endif

#ifndef TEST_HYPERCV_PERFORMANCE
#define SAMPLES_START 10
#define SAMPLES_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  1
#define BANDS_END    2

#else
#define SAMPLES_START 10
#define SAMPLES_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  1
#define BANDS_END    2
#endif

static hyper_mat src_mat = NULL;
static hyper_mat dst_mat = NULL;


static void hypercv_test_setup(int samples, int lines, int bands, int data_type, char interleave[])
{
  	src_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
	hypercv_dataInit<unsigned char>((unsigned char*)src_mat->data,samples,lines,bands);
}

static void test_delete_hyper_mat()
{
	delete_hyper_mat(src_mat);
	delete_hyper_mat(dst_mat);
}

static void test_hyper_mat_rotate()
{

	src_mat = hmread_with_hdr("/home/ljm/Hymap_data.img","/home/ljm/Hymap_data.hdr");
	dst_mat = hyper_mat_rotate(src_mat,45);
	hmsave("test",dst_mat);
	test_delete_hyper_mat();


}

TEST(PROCESS,ROTATE)
{

	test_hyper_mat_rotate();
}
