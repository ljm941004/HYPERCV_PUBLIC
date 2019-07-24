#include "precomp.h"

using namespace std;
#ifndef TEST_HYPERCV_PERFORMANCE
#define ITERS 1
#else
#define ITES 20
#endif

#ifndef TEST_HYPERCV_PERFORMANCE
#define SAMPLE_START 10
#define SAMPLE_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  10
#define BANDS_END    11

#else
#define SAMPLE_START 10
#define SAMPLE_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  10
#define BANDS_END    11
#endif

//static hyper_mat src_mat = NULL;
//static hyper_mat dst_mat = NULL;


static void hypercv_test_setup(int samples, int lines, int bands, int data_type, char interleave[])
{
//	src_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
//	test_hypercv_dataInit<unsigned char>((unsigned char*)src_mat->data,samples,lines,bands)



}



void test_delete_hyper_mat()
{

}

TEST(haha, hss)
{
    printf("haha\n");
    //test_delete_hyper_mat();
}

