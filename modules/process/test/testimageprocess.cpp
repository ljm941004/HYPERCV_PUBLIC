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
#define BANDS_START  10
#define BANDS_END    11

#else
#define SAMPLES_START 10
#define SAMPLES_END   11
#define LINES_START  10
#define LINES_END    11
#define BANDS_START  10
#define BANDS_END    11
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

static void test_bil2bsq()
{
	for(int samples = SAMPLES_START; samples<SAMPLES_END;samples++)
	{
		for(int lines=LINES_START; lines<LINES_END; lines++)
		{
			for(int bands=BANDS_START; bands<BANDS_END; bands++)
			{
				hypercv_test_setup(samples,lines,bands,1,"bil");
				dst_mat = bil2bsq(src_mat);
			}
		}
	}
}
void test_hypermat_get_range()
{	

	hyper_mat t = hyper_mat_get_range(src_mat,20,20,20,80,80,80);
	hyper_mat s = hyper_mat_get_range(src_mat,20,20,20,80,80,80);

}
void test_reshape_hypermat_2_simplemat()
{
	hyper_mat bsq_mat = bil2bsq(src_mat);
	simple_mat mat = reshape_hypermat_2_simplemat(bsq_mat, bsq_mat->bands,bsq_mat->samples*bsq_mat->lines);
}
