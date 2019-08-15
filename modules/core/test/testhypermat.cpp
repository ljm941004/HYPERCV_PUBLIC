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
	dst_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
}

static void test_delete_hyper_mat()
{
	delete_hyper_mat(src_mat);
	delete_hyper_mat(dst_mat);
}

static void test_hmread_hmdelete()
{
	for(int samples = SAMPLES_START; samples<SAMPLES_END; samples++)
	{
		for(int lines = LINES_START; lines<LINES_END; lines++)
		{
			for(int bands = BANDS_START; bands<BANDS_END; bands++)
			{
				hypercv_test_setup(samples,lines,bands,1,(char*)"bsq");
				test_show_mat<char>((char*)src_mat->data,samples,lines,bands);
				test_delete_hyper_mat();
			}
		}  
	}
}

static void test_hyper_mat_copy()
{
	for(int samples = SAMPLES_START; samples<SAMPLES_END; samples++)
	{
		for(int lines = LINES_START; lines<LINES_END; lines++)
		{
			for(int bands = BANDS_START; bands<BANDS_END; bands++)
			{
				hypercv_test_setup(samples,lines,bands,1,(char*)"bsq");
				
				hyper_mat t = hyper_mat_copy(src_mat);

				delete_hyper_mat(t);

				test_delete_hyper_mat();
			}
		}  
	}



}

TEST(CORE,HMDELETE)
{
	test_hmread_hmdelete();
}

