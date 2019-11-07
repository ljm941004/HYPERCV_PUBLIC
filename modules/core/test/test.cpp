/*************************************************************************
	> File Name: test.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

void makeimage()
{

	hyper_mat zaosheng = hmread_with_hdr("/home/ljm/data/data/andianliu","/home/ljm/data/data/andianliu.hdr");
	int zaosheng_size = zaosheng->samples*zaosheng->lines;
	hyper_mat weixing = hmread_with_hdr("/home/ljm/data/data/fy/fengyun180","/home/ljm/data/data/fy/fengyun180.hdr");

	hyper_mat zaoshengbip = bil2bip(zaosheng);
	hyper_mat weixingbip = bil2bip(weixing);
	delete_hyper_mat(zaosheng);
	delete_hyper_mat(weixing);

	hyper_mat dst = create_hyper_mat(768,1366,250,12,"bip");

	int dst_samples = dst->samples;
	int dst_lines = dst->lines;
	int wx_samples = weixingbip->samples;
	int wx_lines = weixingbip->lines;

	int bands = dst->bands;
	unsigned short* dst_data = (unsigned short*)dst->data;
	unsigned short* zs_data = (unsigned short*)zaoshengbip->data;
	unsigned short* wx_data = (unsigned short*)weixingbip->data;

	for(int i=0;i<dst_lines;i++)
	{
		for(int j=0;j<dst_samples;j++)
		{
			unsigned short* dtmp = dst_data+i*dst_samples*bands+j*bands;
			int randnum = rand()%zaosheng_size;
			unsigned short* ztmp = zs_data+randnum*bands;
			memcpy(dtmp,ztmp,bands*sizeof(unsigned short));
		}
	}


	for(int i=0;i<wx_lines;i++)
	{
		unsigned short* dtmp = dst_data+((dst_lines-wx_lines)/2+i)*dst_samples*bands+((dst_samples-wx_samples)/2)*bands;
		unsigned short* wtmp = wx_data+i*wx_samples*bands;

		memcpy(dtmp,wtmp,bands*wx_samples*sizeof(unsigned short));
	}

	hmwrite("fengyun180z",dst);
}
TEST(CORE,MAKEIMAGE)
{
	makeimage();

}
