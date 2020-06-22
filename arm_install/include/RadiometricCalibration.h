/**
* @brief      hyper_mat relative correction.
* @param[in]  bip_mat      hyper mat.
* @param[in]  coefficient    correction coefficient.
* @retval      hyper_mat    hyper image mat.
**/
hyper_mat relative_radiometric_correction(hyper_mat bip_mat, float* coefficient);

/**
* @brief      hyper_mat absolute correction.
* @param[in]  bip_mat      hyper mat.
* @param[in]  coefficient    correction coefficient.
* @retval      hyper_mat    hyper image mat.
**/
hyper_mat absolute_radiometric_correction(hyper_mat bip_mat, float* coefficient);
