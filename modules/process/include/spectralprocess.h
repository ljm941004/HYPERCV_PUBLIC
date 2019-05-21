/**
* @brief      using known spectrum to match all image. 
* @param[in]  bip_data    bip image data.
* @param[in]  spectrum    match spectrum.
* @param[in]  threshold   threshold of match, default 0.8.
**/
unsigned char* spectrum_SAM_match(hyper_mat bip_mat, int spectrum[], float threshold);

/**
* @brief      calculate two vector similar. 
* @param[in]  x           vector x.
* @param[in]  y           vector y.
* @param[in]  length      length of two vector.
* @return     float
**/
float spectral_angle_mapper(unsigned short* x, unsigned short* y, int length);

/**
* @brief      read spectrum from txt file. 
* @param[in]  sp_path     spectrum file path.
* @param[in]  length      length of spectrum.
* @return     spectrum
**/
int* read_spectrum_file(const char* sp_path, int length);