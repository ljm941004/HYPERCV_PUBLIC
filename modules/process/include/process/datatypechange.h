/*************************************************************************
	> File Name: ../include/process/datatypechange.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
/**
* @brief      data type change .
* @param[in]  uc_mat    unsigned char image.
* @retval     dst       short image.
**/
hyper_mat hyper_mat_uchar2short(hyper_mat uc_mat);

/**
* @brief      data type change .
* @param[in]  uc_mat    unsigned char image.
* @retval     dst       int image.
**/
hyper_mat hyper_mat_uchar2int(hyper_mat uc_mat);

/**
* @brief      data type change .
* @param[in]  uc_mat    unsigned char image.
* @retval     dst       float image.
**/
hyper_mat hyper_mat_uchar2float(hyper_mat uc_mat);

/**
* @brief      data type change .
* @param[in]  uc_mat    unsigned char image.
* @retval     dst       unsigned short image.
**/
hyper_mat hyper_mat_uchar2ushort(hyper_mat uc_mat);

/**
* @brief      data type change .
* @param[in]  f_mat      float image.
* @retval     dst        char image.
**/
hyper_mat hyper_mat_float2char(hyper_mat f_mat);

/**
* @brief      data type change .
* @param[in]  f_mat      float image.
* @retval     dst        int image.
**/
hyper_mat hyper_mat_float2int(hyper_mat f_mat);


/**
* @brief      data type change .
* @param[in]  f_mat      float image.
* @retval     dst        short image.
**/
hyper_mat hyper_mat_float2short(hyper_mat f_mat);

/**
 * @brief      data type change .
 * @param[in]  f_mat      float image.
 * @retval     dst        unsigned short image.
 **/
hyper_mat hyper_mat_float2ushort(hyper_mat f_mat);

float hypercv_atof(const char *str);

/**
 * @brief      data type change .
 * @param[in]  f_mat      unsined short image.
 * @retval     dst        float image.
 **/
hyper_mat hyper_mat_ushort2float(hyper_mat us_mat);

/**
 * @brief      data type change .
 * @param[in]  f_mat      float image.
 * @retval     dst        unsigned char image.
 **/
hyper_mat hyper_mat_float2uchar(hyper_mat f_mat);
