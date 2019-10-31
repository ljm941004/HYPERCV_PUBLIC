/*************************************************************************
	> File Name: ../include/process/datatypechange.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/


hyper_mat hyper_mat_float2char(hyper_mat f_mat);

hyper_mat hyper_mat_float2int(hyper_mat f_mat);


hyper_mat hyper_mat_float2short(hyper_mat f_mat);


hyper_mat hyper_mat_float2ushort(hyper_mat f_mat);

float hypercv_atof(const char *str);

/**
 * @brief      data type change .
 * @param[in]  f_mat      unsined short image.
 * @retval     dst        float image.
 **/
hyper_mat hyper_mat_ushort2float(hyper_mat us_mat);
