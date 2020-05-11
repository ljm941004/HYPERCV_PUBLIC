/*************************************************************************
  > File Name: satellite_orbit.c
  > Author: ljm
  > Mail: jimin@iscas.ac.cn 
  > Created Time: 2020年05月11日 星期一 20时19分28秒
 ************************************************************************/
#include "precomp.h"
/**
 * @brief      parameter of satellite orbit.
 *      long double as,      // 轨道长半轴
 long double es,      // 轨道偏心率
 long double omega,   // 升交点赤经
 long double ws,      // 近地点幅角
 long double M0,      // 平近点角
 long double i,       // 轨道倾角(弧度)
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
 long double omegadot
 **/
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
		long double omegadot)
{
	sat_orbit orb;
	orb->as = as;
	orb->es = es;
	orb->omega = omega;
	orb->ws = ws;
	orb->M0 = M0;
	orb->i0 = i0;
	orb->idot = idot;
	orb->delta_n = delta_n;
	orb->toe = toe;
	orb->t = t;
	orb->cus = cus;
	orb->cuc = cuc;
	orb->crs = crs;
	orb->crc = crc;
	orb->cis = cis;
	orb->cic = cic;
	orb->omegadot = omegadot;

	orb->n0 = sqrt(bGM84 / (as*as*as));
	orb->n = orb->n0 + orb->delta_n;

	orb->Mk = orb->M0 + orb->n*orb->tk;

	for (int i = 0; i < 10; i++)
		orb->E = orb->Mk + orb->es*sin(orb->E);

	orb->f = 2 * atan(sqrt((1 + orb->es) / (1 - orb->es))* (tan(orb->E)) / 2);

	orb->phik = orb->f + orb->ws;

	orb->corr_u = orb->cus*sin(2.0*orb->phik) + orb->cuc*cos(2.0*orb->phik);//升交距角u的摄动改正δu
	orb->corr_r = orb->crs*sin(2.0*orb->phik) + orb->crc*cos(2.0*orb->phik);//卫星矢量r的摄动改正δr
	orb->corr_i = orb->cis*sin(2.0*orb->phik) + orb->cic*cos(2.0*orb->phik);//轨道倾角i的摄动改正δi

	orb->uk = orb->phik + orb->corr_u;

	orb->r = orb->as*(1 - orb->es*cos(orb->E)) + orb->corr_r;

	orb->ik = orb->i0 + orb->idot*orb->tk + orb->corr_i;
	orb->omegak = orb->omega + (orb->omegadot - bOMEGAE84)*orb->tk - bOMEGAE84*orb->toe;

	return orb;
}

ECEF get_satellite_position_ecef(sat_orbit orb)
{
	ECEF coordinate;

	coordinate.ecefx = orb->r*cos(orb->uk)*cos(orb->omegak) - orb->r*sin(orb->uk)*sin(orb->omegak)*cos(orb->ik);

	coordinate.ecefy = orb->r*cos(orb->uk)*sin(orb->omegak) + orb->r*sin(orb->uk)*cos(orb->omegak)*cos(orb->ik);

	coordinate.ecefz = orb->r*sin(orb->uk)*sin(orb->ik);
	
	return coordinate;
}


