/*************************************************************************
	> File Name: process/include/process/dwt.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#pragma once
#define HYPERCV_WAVE_DB3 1
#define HYPERCV_WAVE_BIOR3_7 2 

/* 小波变换信息描述结构体 */
typedef struct wtInfo {
	int wave_type;	// 小波类型
	int border_type;		// 延拓方式
	int wt_level;		// 变换级数
	double * c;		// 变换结果，小波系数，[An, Hn, Vn, Dn, H(n-1), V(n-1), D(n-1)..., H1, V1, D1]
	int * s;			// 变换结果描述，一个2*n数组，其中n = WTLevel+2；
} wt_info;


/* 小波变换结果描述结构体 */
typedef struct WTCoefSet{
	simple_mat A_LL;		// 低通分量
	simple_mat H_LH;		// 水平分量分量
	simple_mat V_HL;		// 竖直分量
	simple_mat D_HH;		// 对角分量
} wt_coefset;


/* 小波基常量描述结构体 */
typedef struct waveletBase {
	int len;
	double * LO_D;
	double * HI_D;
	double * LO_R;
	double * HI_R;
}wavelet_base;


