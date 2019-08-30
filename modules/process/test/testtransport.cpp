/*************************************************************************
	> File Name: testtransport.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
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
	dst_mat = create_hyper_mat(lines,samples,bands,data_type,interleave);
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

static void test_hyper_mat_transport()
{
	
	for(int samples = SAMPLES_START; samples<SAMPLES_END;samples++)
	{
		for(int lines=LINES_START; lines<LINES_END; lines++)
		{
			for(int bands=BANDS_START; bands<BANDS_END; bands++)
			{
				hypercv_test_setup<char>(samples,lines,bands,1,(char*)"bsq");
				hyper_mat_transport(src_mat,dst_mat);

	for(int i=0;i<3;i++)
					cout<<dst_mat->interleave[i];
//todo fix bsq bug	return;	
	t = create_hyper_mat(samples,lines,bands,1,(char*)"bsq");
			
				for(int i=0;i<3;i++)
					cout<<t->interleave[i];
				hyper_mat_transport(dst_mat,t);
				
				int tmp = hypercv_mat_compare<char>((char*)src_mat->data,(char*)t->data,samples,lines,bands);
				_assert(tmp==0,"hyper_mat_copy_wrong");

				test_delete_hyper_mat();
			}
		}
	}
}

TEST(PROCESS,TRANSPORT)
{
	test_hyper_mat_transport();
}
