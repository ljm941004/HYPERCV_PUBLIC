/*************************************************************************
	> File Name: modules/satellite/src/satellite_attitude.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年05月11日 星期一 20时26分39秒
 ************************************************************************/
void cal_satellite_attitude(quaternion Q, Euler_angle  &angle)
{
	double q1 = Q.q1;
	double q2 = Q.q2;
	double q3 = Q.q3;
	double q4 = Q.q4;
	double g1 = 2 * (q1*q2 - q3*q4);
	double g2 = -q1*q1 + q2*q2 - q3*q3 + q4*q4;
	double g3 = 2 * (q2*q3 + q1*q4);
	double g4 = 2 * (q1*q3 - q2*q4);
	double g5 = -q1*q1 - q2*q2 + q3*q3 + q4*q4;
	angle.x = -atanf(g1 / g2) ;//翻滚角
	angle.y = asinf(g3) ;//俯仰角
	angle.z = atanf(g4 / g5);//偏航角
}

