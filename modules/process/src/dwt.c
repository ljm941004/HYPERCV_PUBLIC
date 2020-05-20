/*************************************************************************
	> File Name: dwt.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
/************************************************************************
 *                            private function
 ************************************************************************/
/* db3小波滤波器 */
static double LO_D_db3[6] = {0.0352, -0.0854, -0.1350, 0.4599, 0.8069, 0.3327};
static double HI_D_db3[6] = {-0.3327, 0.8069, -0.4599, -0.1350, 0.0854, 0.0352};
static double LO_R_db3[6] = {0.3327, 0.8069, 0.4599, -0.1350, -0.0854, 0.0352};
static double HI_R_db3[6] = {0.0352, 0.0854, -0.1350, -0.4599, 0.8069, -0.3327};
static wavelet_base WAVEdb3 = {6, LO_D_db3, HI_D_db3, LO_R_db3, HI_R_db3};

/* bior3.7小波滤波器 */
static double LO_D_bior3_7[] = {0.0030, -0.0091, -0.0168, 0.0747, 0.0313, -0.3012, -0.0265, 0.9516, 0.9516, -0.0265, -0.3012, 0.0313, 0.0747, -0.0168, -0.0091, 0.0030};
static double HI_D_bior3_7[] = {0,  0,  0,  0,  0,  0, -0.1768, 0.5303, -0.5303, 0.1768,  0,  0,  0,  0,  0,  0};
static double LO_R_bior3_7[] = {0,  0,  0,  0,  0,  0, 0.1768, 0.5303, 0.5303, 0.1768,  0,  0,  0,  0,  0,  0};
static double HI_R_bior3_7[] = {0.0030, 0.0091, -0.0168, -0.0747, 0.0313, 0.3012, -0.0265, -0.9516, 0.9516, 0.0265, -0.3012, -0.0313, 0.0747, 0.0168, -0.0091, -0.0030};
static  wavelet_base WAVEbior3_7 = {16, LO_D_bior3_7, HI_D_bior3_7, LO_R_bior3_7, HI_R_bior3_7};

static double* SerialReverse(double * src, int len)
{
	int i;
	double * result = NULL;

	result = (double *) calloc(len, sizeof(double));
	if (!result)
		exit(1);

	for (i = 0; i < len; i++)
		result[i] = src[len-i-1];
	return result;
}

wt_coefset* sub_wavedec(simple_mat src, wavelet_base* wb, int border_type)
{
	wt_coefset* res = NULL;

	simple_mat A_LL;
	simple_mat H_LH;
	simple_mat V_HL;
	simple_mat D_HH;

	simple_mat A_LL2;
	simple_mat V_HL2;
	simple_mat D_HH2;
	simple_mat H_LH2;

	simple_mat extmat;
	simple_mat A_H;
	simple_mat V_D;
	simple_mat A_H2;
	simple_mat V_D2;

	res = (wt_coefset*)calloc(1,sizeof(wt_coefset));

	extmat = hypercv_copy_make_border(src,wb->len-1,wb->len-1,wb->len-1,wb->len-1,border_type,0);
	//todo




}


/**************************************************************************
 *                        public function
 **************************************************************************/

void wt_coefset_free(wt_coefset* cs)
{
	if(cs!=NULL)
	{
		if(cs->A_LL !=NULL)
			free(cs->A_LL);
		if(cs->H_LH!=NULL)
			free(cs->H_LH);
		if(cs->V_HL!=NULL)
			free(cs->V_HL);
		if(cs->D_HH!=NULL)
			free(cs->D_HH);
		free(cs);
	}
}


void wavelet_base_free(wavelet_base* wb)
{
	if(wb!=NULL)
	{
		if(wb->LO_D!=NULL)
			free(wb->LO_D);
		if(wb->HI_D!=NULL)
			free(wb->HI_D);
		if(wb->LO_R!=NULL)
			free(wb->LO_R);
		if(wb->HI_D!=NULL)
			free(wb->HI_R);
		free(wb);
	}
}

void wt_info_free(wt_info* wt_if)
{
	if(wt_if!=NULL)
	{
		if(wt_if->c != NULL)
			free(wt_if->c);
		if(wt_if->s != NULL)
			free(wt_if->s);
		free(wt_if);
	}
}


wavelet_base* set_wavelet_base(int wave_type)
{
	hypercv_assert(wave_type!=HYPERCV_WAVE_DB3||wave_type!=HYPERCV_WAVE_BIOR3_7,"ERROR WAVE TYPE")
	wavelet_base *wb;
	wb = (wavelet_base*) calloc(1,sizeof(wavelet_base));
	
	switch(wave_type)
	{
		case HYPERCV_WAVE_DB3:
			wb->len = WAVEdb3.len;
			wb->LO_D = SerialReverse(WAVEdb3.LO_D,WAVEdb3.len);
			wb->HI_D = SerialReverse(WAVEdb3.HI_D,WAVEdb3.len);
		    wb->LO_R = SerialReverse(WAVEdb3.LO_R,WAVEdb3.len);
		    wb->HI_R = SerialReverse(WAVEdb3.HI_R,WAVEdb3.len);
			break;
        case HYPERCV_WAVE_BIOR3_7:
            wb->len = WAVEbior3_7.len;
			wb->LO_D = SerialReverse(WAVEbior3_7.LO_D,WAVEbior3_7.len);
			wb->HI_D = SerialReverse(WAVEbior3_7.HI_D,WAVEbior3_7.len);
		    wb->LO_R = SerialReverse(WAVEbior3_7.LO_R,WAVEbior3_7.len);
		    wb->HI_R = SerialReverse(WAVEbior3_7.HI_R,WAVEbior3_7.len);
			break;
	}
	return wb;
}

wt_info* hypercv_wavedec(simple_mat src, int wt_level, int wave_type, int border_type)
{
	hypercv_assert(src!=NULL,"input mat cannot be NULL");

	//int i,j,k;
	//int coef_len;
	wt_info* res = NULL;

	simple_mat temp = simple_mat_copy(src); 
	wt_coefset ** cs = NULL;
	wavelet_base * wb = NULL;

	if(!(res = (wt_info*)calloc(1,sizeof(wt_info))))
		exit(1);
	res -> wave_type = wave_type;
	res -> border_type = border_type;
	res -> wt_level = wt_level;
	res -> c = NULL;
	res -> s = NULL;

	cs = (wt_coefset **)calloc(wt_level,sizeof(wt_coefset*));

	for(int i=0;i<wt_level;i++)
	{
	//	cs[i] = 
	}
	//todo fix 
}



void hypercv_dwt1D_float(float* signal, float* res, int length)
{
//todo fix;



}
