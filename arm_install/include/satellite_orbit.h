/*************************************************************************
  > File Name: satellite_orbit.h
  > Author: ljm
  > Mail: jimin@iscas.ac.cn 
  > Created Time: 2020年05月11日 星期一 20时17分19秒
 ************************************************************************/
/**
 * @brief      parameter of satellite orbit.
 **/

#ifndef bGM84
#define bGM84 3.986005e14
#endif

#ifndef bOMEGAE84
#define bOMEGAE84 7.2921151467e-5
#endif

typedef struct ORBIT_COORINATE_SYSTEM
{
	double orbx;
	double orby;
}ORB_C;

typedef struct ECEF_SYSTEM
{
	double ecefx;
	double ecefy;
	double ecefz;
}ECEF;

typedef struct SATELLITE_ORBIT
{
	long double as;      // 轨道长半轴
	long double es;      // 轨道偏心率
	long double omega;   // 升交点赤经
	long double ws;      // 近地点幅角
	long double M0;      // toe时刻平近点角
	long double i0;       // 轨道倾角(弧度)
	long double idot;    // 轨道倾角变化率I
	long double delta_n; // 卫星的摄动改正数△n
	long double toe;     // 观测时刻
	long double t;       // 加入卫星钟差改正的归化时间
	long double cus;    // 纬度幅角正弦调和项改正的振幅（弧度）
	long double cuc;     // 纬度幅角余弦调和项改正的振幅（弧度）
	long double crs;     // 轨道半径的余弦调和项改正的振幅（m）
	long double crc;     // 轨道半径的正弦调和项改正的振幅（m）
	long double cis;     // 轨道倾角的余弦调和项改正的振幅（弧度）
	long double cic;     // 轨道倾角的正弦调和项改正的振幅（弧度）
	long double omegadot; //升交点变化率
	
	long double f;       // 真近点角
	long double r;       // 卫星到地心得距离
	long double n0;       // 平均角速度
	long double tk;       // 相对于参考时刻toe的归化时间tk
	long double n;       // 加摄动改正后的卫星平均角速度
	long double Mk;       // 平近点角
	long double E;       // 偏近点角
	long double phik;       // 升交距角φk0

	long double corr_u;     //升交距角u的摄动改正δu
	long double corr_r;     //卫星矢量r的摄动改正δr
	long double corr_i;     //轨道倾角i的摄动改正δi

	long double uk;         // 升交距角u
	long double ik;         // 轨道倾角
	long double omegak;     // 升交点经度Ωk
}SATELLITE_ORBIT;

typedef SATELLITE_ORBIT* sat_orbit;


sat_orbit hypercv_create_orbit(long double as,      // 轨道长半轴
		long double es,      // 轨道偏心率
		long double omega,   // 升交点赤经
		long double ws,      // 近地点幅角
		long double M0,      // 平近点角
		long double i0,       // 轨道倾角(弧度)
		long double idot,    // 轨道倾角变化率I
		long double delta_n, // 卫星的摄动改正数△n
		long double toe,     // 观测时刻
		long double t,       // 加入卫星钟差改正的归化时间
		long double cus,     // 纬度幅角正弦调和项改正的振幅（弧度）
		long double cuc,     // 纬度幅角余弦调和项改正的振幅（弧度）
		long double crs,     // 轨道半径的余弦调和项改正的振幅（m）
		long double crc,     // 轨道半径的正弦调和项改正的振幅（m）
		long double cis,     // 轨道倾角的余弦调和项改正的振幅（弧度）
		long double cic,
		long double omegadot);



ECEF get_satellite_position_ecef(sat_orbit orb);


