/*************************************************************************
	> File Name: modules/satellite/include/satellite/satellite_attitude.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年05月11日 星期一 20时29分06秒
 ************************************************************************/
struct quaternion
{
	double q1;
	double q2;
	double q3;
	double q4;
};
 
struct Euler_angle
{
	double x;  // 滚动角x，
	double y;  // 俯仰角y
	double z;  // 偏航角z
};

