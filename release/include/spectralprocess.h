/**
* @brief      using known spectrum to match all image.
* @param[in]  bip_data    bip image data.
* @param[in]  spectrum    match spectrum.
* @param[in]  threshold   threshold of match, default 0.8.
**/
simple_mat spectrum_SAM_match(hyper_mat bip_mat, float* spectrum, float threshold);

/**
* @brief      calculate two vector similar.
* @param[in]  x           vector x.
* @param[in]  y           vector y.
* @param[in]  length      length of two vector.
* @retval     float
**/
float spectral_angle_mapper(float* x, float* y, int length);

/**
* @brief      read spectrum from txt file.
* @param[in]  sp_path     spectrum file path.
* @param[in]  length      length of spectrum.
* @retval     spectrum
**/
float* read_spectrum_file(const char* sp_path, int length);

/**
* @brief      calculate two vector similar.
* @param[in]  x           vector x.
* @param[in]  y           vector y.
* @param[in]  length      length of two vector.
**/
float euclidean_distance(float * x, float * y, int length);