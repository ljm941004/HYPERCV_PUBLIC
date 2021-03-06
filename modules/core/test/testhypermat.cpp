#include "precomp.h"

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
#define SAMPLES_END   1024
#define LINES_START  10
#define LINES_END    1024
#define BANDS_START  10
#define BANDS_END    1024
#endif

static hyper_mat src_mat = NULL;
static hyper_mat dst_mat = NULL;
static hyper_mat t = NULL;

template<typename type>
static void hypercv_test_setup(int samples, int lines, int bands, int data_type, char interleave[])
{
  	src_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
	hypercv_dataInit<type>((type*)src_mat->data,samples,lines,bands);
	dst_mat = create_hyper_mat(samples, lines, bands, data_type, interleave);
}

static void test_delete_hyper_mat()
{
	if(src_mat!=NULL)
		delete_hyper_mat(src_mat);
	if(dst_mat!=NULL)
		delete_hyper_mat(dst_mat);
	if(t!=NULL)
		delete_hyper_mat(t);
}

static void test_hmread_with_hdr_hmdelete()
{
	for(int samples = SAMPLES_START; samples<SAMPLES_END; samples++)
	{
		for(int lines = LINES_START; lines<LINES_END; lines++)
		{
			for(int bands = BANDS_START; bands<BANDS_END; bands++)
			{
				hypercv_test_setup<char>(samples,lines,bands,1,(char*)"bsq");
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
				hypercv_test_setup<unsigned char>(samples,lines,bands,1,(char*)"bsq");
					
				hyper_mat t = hyper_mat_copy(src_mat);
				int tmp = hypercv_mat_compare<char>((char*)src_mat->data,(char*)t->data,samples,lines,bands);
				
				hypercv_assert(tmp==0,"hyper_mat_copy_wrong");

				test_delete_hyper_mat();
			}
		}  
	}

}

static void test_write_hdr()
{
    const char* image_path = "image";
	int samples = 10;
	int lines = 10;
	int bands = 10;
	int data_type = 1;
	const char* interleave = "bsq";

	writehdr(image_path, samples, lines, bands, data_type, interleave,NULL );
}

static void test_hmread_with_hdr()
{
	const char* image_path = "/home/ljm/Hymap_data.img";
	const char* hdr_path = "/home/ljm/Hymap_data.hdr";

    hyper_mat t = hmread_with_hdr(image_path,hdr_path);
	for(int i=0;i<t->bands;i++)
		printf("%f,",t->wavelength[i]);
}


static void test_read_wavelength()
{

	const char* hdr_path = "/home/ljm/Hymap_data.hdr";

	FILE* hdr_fp = NULL;

	hdr_fp = fopen(hdr_path, "r");

	char line[100000];
	char item[100000];

	while(fgets(line,100000,hdr_fp)!=0)
	{
		sscanf(line,"%[^=]",item);
		printf("%c\n",line[strlen(line)-3]);

	}



}

static void test_readHdr()
{

	hyper_mat t = create_hyper_mat(3,3,3,1,"bsq");

	hmsave("test",t);

	int samples,lines,bands,dataType,format;
	float* wavelength = (float*)malloc(bands*sizeof(float));

    readHdr("test.hdr", samples, lines, bands, dataType,format, wavelength);

	cout<<samples<<lines<<bands;
	for(int i =0 ;i<bands;i++)
		cout<<wavelength[i];


}


TEST(CORE,READHDR)
{
	test_readHdr();
}

TEST(CORE,HMCOPY)
{
	test_hyper_mat_copy();
}

TEST(CORE,HMDELETE)
{
	test_hmread_with_hdr_hmdelete();
}

TEST(CORE,WRITEHDR)
{
	test_write_hdr();
}
TEST(CORE,HMREAD_WITH_HDR)
{
	test_hmread_with_hdr();
}
TEST(CORE,READ_WAVELENGTH)
{
	test_read_wavelength();
}
