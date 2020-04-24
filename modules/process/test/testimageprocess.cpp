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
				hypercv_test_setup(samples,lines,bands,1,(char*)"bil");
				dst_mat = bil2bsq(src_mat);
			}
		}
	}
}
void test_hypermat_get_range()
{	
   hyper_mat r = hmread_with_hdr("/home/ljm/res","/home/ljm/res.hdr");
   hyper_mat t = hyper_mat_get_range(r,0,0,0,395,156,1);
   hmsave("res",t);

}
void test_reshape_hypermat_2_simplemat()
{
	hyper_mat bsq_mat = bil2bsq(src_mat);
	simple_mat mat = reshape_hypermat_2_simplemat(bsq_mat, bsq_mat->bands,bsq_mat->samples*bsq_mat->lines);
}

void test_convert2()
{
	hyper_mat mat = hmread_with_hdr("/home/ljm/Hymap_data.img","/home/ljm/Hymap_data.hdr");
	for(int i=0;i<mat->bands;i++)
		printf("%f,",mat->wavelength[i]);
	printf("%s\n",mat->interleave);
	convert2bil(mat);
	for(int i=0;i<mat->bands;i++)
		printf("%f,",mat->wavelength[i]);
	printf("%s\n",mat->interleave);
	hmsave("bil",mat);
	convert2bsq(mat);
	for(int i=0;i<mat->bands;i++)
		printf("%f,",mat->wavelength[i]);
	printf("%s\n",mat->interleave);
	hmsave("bsq",mat);
	convert2bip(mat);
	for(int i=0;i<mat->bands;i++)
		printf("%f,",mat->wavelength[i]);
	printf("%s\n",mat->interleave);
	hmsave("bip",mat);
	delete_hyper_mat(mat);

}

TEST(PROCESS,CONVERT)
{
	test_convert2();
}

TEST(PROCESS,GETRANGE)
{
	test_hypermat_get_range();
}
