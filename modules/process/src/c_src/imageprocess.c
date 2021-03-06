#include "precomp.h"


void convert2bsq(hyper_mat mat)
{
	hypercv_assert(mat!=NULL,"input mat cannot be NULL");

	hyper_mat res;

	if(cmpstr(mat -> interleave,"bsq") == 1)
	    return; 
	else if(cmpstr(mat -> interleave,"bil") == 1)
	{
		res = bil2bsq(mat);
		hyper_mat_copy_to(res,mat);
		delete_hyper_mat(res);
		return;
	}
	else if(cmpstr(mat -> interleave,"bip") == 1)
	{
		res = bip2bsq(mat);
		hyper_mat_copy_to(res,mat);
		delete_hyper_mat(res);
		return;
	}
}

void convert2bil(hyper_mat mat)
{
	hypercv_assert(mat!=NULL,"input mat cannot be NULL");

	hyper_mat res;

	if(cmpstr(mat -> interleave,"bil") == 1)
		return;
	else if(cmpstr(mat -> interleave,"bsq") == 1)
	{
		res = bsq2bil(mat);
		hyper_mat_copy_to(res,mat);
		delete_hyper_mat(res);
		return;
	}
	else if(cmpstr(mat -> interleave,"bip") == 1)
	{
		res = bip2bil(mat);
		hyper_mat_copy_to(res,mat);
		delete_hyper_mat(res);
		return;
	}

}

void convert2bip(hyper_mat mat)
{
	hypercv_assert(mat!=NULL,"input mat cannot be NULL");

	hyper_mat res;

	if(cmpstr(mat -> interleave,"bip") == 1)
		return;
	else if(cmpstr(mat -> interleave,"bil") == 1)
	{
		res = bil2bip(mat);
		hyper_mat_copy_to(res,mat);
		delete_hyper_mat(res);
		return;
	}
	else if(cmpstr(mat -> interleave,"bsq") == 1)
	{
		res = bsq2bip(mat);
		hyper_mat_copy_to(res,mat);
		delete_hyper_mat(res);
		return;
	}

}

/**
* @brief      transform bil to bsq.
* @param[in]  bil_mat    bil image.
* @retval     bsq_mat    bsq image.
**/
hyper_mat bil2bsq(hyper_mat bil_mat)
{
	hypercv_assert(bil_mat != NULL,"hyper_mat can not be NULL");

	if(cmpstr(bil_mat -> interleave,"bsq") == 1)
		return hyper_mat_copy(bil_mat);

	hypercv_assert(cmpstr(bil_mat -> interleave,"bil") == 1, "input hyper mat's interleave must be bil");

	int samples   = bil_mat -> samples;
	int lines     = bil_mat -> lines;
	int bands     = bil_mat -> bands;
	int elem_size = get_elemsize(bil_mat->data_type);

	hyper_mat bsq_mat = create_hyper_mat(samples, lines, bands, bil_mat->data_type, "bsq");

	char* bil_data = (char*)bil_mat -> data;
	char* bsq_data = (char*)bsq_mat -> data;

	unsigned int bil_index = 0, bsq_index = 0;

	for (int k=0; k<bands; k++)
	{
		for (int i=0; i<lines; i++)
		{
			for (int j=0; j<samples; j++)
			{
				bil_index = (i*samples*bands + k*samples + j)*elem_size;
				bsq_index = (k*samples*lines + i*samples + j)*elem_size;

				for (int t=0; t<elem_size; t++)
					bsq_data[bsq_index + t] = bil_data[bil_index + t];
			}
		}
	}

	float* bil_wave = (float*)bil_mat->wavelength;
	float* bsq_wave = (float*)bsq_mat->wavelength;

	if(bil_wave != NULL)
		memcpy(bsq_wave, bil_wave, bands*sizeof(float));

	return bsq_mat;
}

/**
* @brief      transform bil to bip.
* @param[in]  bil_mat    bil image.
* @retval     bip_mat    bip image. 
**/
hyper_mat bil2bip(hyper_mat bil_mat)
{
	hypercv_assert(bil_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bil_mat -> interleave,"bip") == 1)
		return hyper_mat_copy(bil_mat);

	hypercv_assert(cmpstr(bil_mat -> interleave,"bil") == 1, "input hyper mat's interleave must be bil");

	int samples   = bil_mat -> samples;
	int lines     = bil_mat -> lines;
	int bands     = bil_mat -> bands;
	int elem_size = get_elemsize(bil_mat->data_type);

	hyper_mat bip_mat = create_hyper_mat(samples, lines, bands, bil_mat->data_type, "bip");

	char* bil_data = (char*)bil_mat -> data;
	char* bip_data = (char*)bip_mat -> data;

	unsigned int bil_index = 0, bip_index = 0;

	for (int i=0;i<lines; i++)
	{
		for (int j=0;j<samples; j++)
		{
			for (int k=0; k<bands; k++)
			{
				bil_index = (i*samples*bands + k*samples + j)*elem_size;
				bip_index = (i*samples*bands + j*bands + k)*elem_size;

				for (int t=0; t<elem_size; t++)
					bip_data[bip_index + t] = bil_data[bil_index + t];
			}
		}
	}

	float* bil_wave = (float*)bil_mat->wavelength;
	float* bip_wave = (float*)bip_mat->wavelength;

	if(bil_wave != NULL)
		memcpy(bip_wave, bil_wave, bands*sizeof(float));

	return bip_mat;
}

/**
* @brief      transform bsq to bil.
* @param[in]  bsq_mat    bsq image.
* @retval     bip_mat    bil image. 
**/
hyper_mat bsq2bil(hyper_mat bsq_mat)
{
	hypercv_assert(bsq_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bsq_mat -> interleave,"bil") == 1)
		return hyper_mat_copy(bsq_mat);

	hypercv_assert(cmpstr(bsq_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");

	int samples   = bsq_mat -> samples;
	int lines     = bsq_mat -> lines;
	int bands     = bsq_mat -> bands;
	int elem_size = get_elemsize(bsq_mat->data_type);

	hyper_mat bil_mat = create_hyper_mat(samples, lines, bands, bsq_mat->data_type, "bil");

	char* bsq_data = (char*)bsq_mat -> data;
	char* bil_data = (char*)bil_mat -> data;

	unsigned int bsq_index = 0, bil_index = 0;

	for (int i=0;i<lines; i++)
	{
		for (int k=0; k<bands; k++)
		{
			for (int j=0;j<samples; j++)
			{
				bsq_index = (k*samples*lines + i*samples + j)*elem_size;
				bil_index = (i*samples*bands + k*samples + j)*elem_size;

				for (int t=0; t<elem_size; t++)
					bil_data[bil_index + t] = bsq_data[bsq_index + t];
			}
		}
	}

	float* bil_wave = (float*)bil_mat->wavelength;
	float* bsq_wave = (float*)bsq_mat->wavelength;

	if(bsq_wave != NULL)
		memcpy(bil_wave, bsq_wave, bands*sizeof(float));

	return bil_mat;
}

/**
* @brief      transform bsq to bip.
* @param[in]  bil_mat    bsq image.
* @retval     bip_mat    bip image. 
**/
hyper_mat bsq2bip(hyper_mat bsq_mat)
{
	hypercv_assert(bsq_mat != NULL,"hyper_mat can not be NULL");

	if(cmpstr(bsq_mat -> interleave,"bip") == 1)
		return hyper_mat_copy(bsq_mat);

	hypercv_assert(cmpstr(bsq_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");

	int samples   = bsq_mat -> samples;
	int lines     = bsq_mat -> lines;
	int bands     = bsq_mat -> bands;
	int elem_size = get_elemsize(bsq_mat->data_type);


	hyper_mat bip_mat = create_hyper_mat(samples, lines, bands, bsq_mat->data_type, "bip");

	char* bsq_data = (char*)bsq_mat -> data;
	char* bip_data = (char*)bip_mat -> data;

	unsigned int bsq_index = 0, bip_index = 0;

	for (int i=0;i<lines; i++)
	{
		for (int j=0;j<samples; j++)
		{
			for (int k=0; k<bands; k++)
			{
				bsq_index = (k*samples*lines + i*samples + j)*elem_size;
				bip_index = (i*samples*bands + j*bands + k)*elem_size;

				for (int t=0; t<elem_size; t++)
					bip_data[bip_index + t] = bsq_data[bsq_index + t];
			}
		}
	}
    
	float* bip_wave = (float*)bip_mat->wavelength;
	float* bsq_wave = (float*)bsq_mat->wavelength;

	if(bsq_wave != NULL)
		memcpy(bip_wave, bsq_wave, bands*sizeof(float));

	return bip_mat;
}

/**
* @brief      transform bip to bsp.
* @param[in]  bil_mat    bip image.
* @retval     bip_mat    bsq image. 
**/
hyper_mat bip2bsq(hyper_mat bip_mat)
{
	hypercv_assert(bip_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bip_mat -> interleave,"bsq") == 1)
		return hyper_mat_copy(bip_mat);

	hypercv_assert(cmpstr(bip_mat -> interleave,"bip") == 1, "input hyper mat's interleave must be bip");

	int samples   = bip_mat -> samples;
	int lines     = bip_mat -> lines;
	int bands     = bip_mat -> bands;
	int elem_size = get_elemsize(bip_mat->data_type);

	hyper_mat bsq_mat = create_hyper_mat(samples, lines, bands, bip_mat->data_type, "bsq");

	char* bip_data = (char*)bip_mat -> data;
	char* bsq_data = (char*)bsq_mat -> data;

	unsigned int bsq_index = 0, bip_index = 0;

	for (int i=0;i<lines; i++)
	{
		for (int j=0;j<samples; j++)
		{
			for (int k=0; k<bands; k++)
			{
				bsq_index = (k*samples*lines + i*samples + j)*elem_size;
				bip_index = (i*samples*bands + j*bands + k)*elem_size;

				for (int t=0; t<elem_size; t++)
					bsq_data[bsq_index + t] = bip_data[bip_index + t]  ;
			}
		}
	}

	float* bip_wave = (float*)bip_mat->wavelength;
	float* bsq_wave = (float*)bsq_mat->wavelength;

	if(bip_wave != NULL)
		memcpy(bsq_wave, bip_wave, bands*sizeof(float));

	return bsq_mat;
}

/**
* @brief      transform bip to bil .
* @param[in]  bip_mat    bip image.
* @retval     bil_mat    bil image. 
**/
hyper_mat bip2bil(hyper_mat bip_mat)
{
	hypercv_assert(bip_mat != NULL,                "hyper_mat can not be NULL");
	if(cmpstr(bip_mat -> interleave,"bil") == 1)
		return hyper_mat_copy(bip_mat);
	hypercv_assert(cmpstr(bip_mat -> interleave,"bip") == 1, "input hyper mat's interleave must be bip");

	int samples   = bip_mat -> samples;
	int lines     = bip_mat -> lines;
	int bands     = bip_mat -> bands;
	int elem_size = get_elemsize(bip_mat->data_type);

	hyper_mat bil_mat = create_hyper_mat(samples, lines, bands, bip_mat->data_type, "bil");

	char* bip_data = (char*)bip_mat -> data;
	char* bil_data = (char*)bil_mat -> data;

	unsigned int bil_index = 0, bip_index = 0;

	for (int i=0;i<lines; i++)
	{
		for (int j=0;j<samples; j++)
		{
			for (int k=0; k<bands; k++)
			{
				bil_index = (i*samples*bands + k*samples + j)*elem_size;
				bip_index = (i*samples*bands + j*bands + k)*elem_size;

				for (int t=0; t<elem_size; t++)
					bil_data[bil_index + t] = bip_data[bip_index + t];
			}
		}
	}

	float* bil_wave = (float*)bil_mat->wavelength;
	float* bip_wave = (float*)bip_mat->wavelength;

	if(bip_wave != NULL)
		memcpy(bil_wave, bip_wave, bands*sizeof(float));

	return bil_mat;
}

/**
* @brief      get roi data from hyper data.
* @param[in]  src_mat     hyper image.
* @param[in]  start_row   start row of roi.
* @param[in]  start_col   start col of roi.
* @param[in]  start_band  start band of roi.
* @param[in]  end_row     end row of roi.
* @param[in]  end_col     end col of roi.
* @param[in]  end_band    end band of roi.
* @retval     dst_mat     hyper image. 
**/
hyper_mat hyper_mat_get_range(hyper_mat src_mat, int start_row, int start_col, int start_band, int end_row, int end_col, int end_band)
{
	hypercv_assert(start_col<end_col && start_row<end_row && start_band<end_band, "start col & start row & start band must < end col & end row & end band");

	int samples = end_col - start_col;
	int lines = end_row - start_row;
	int bands = end_band - start_band;
	int data_type = src_mat -> data_type;

	hyper_mat dst_mat = create_hyper_mat(samples, lines, bands, data_type, src_mat -> interleave);

	int elem_size = get_elemsize(data_type);

	char* src_data = (char*)src_mat->data;
	char* dst_data = (char*)dst_mat->data;

	int src_index =0, dst_index =0;
	int src_samples = src_mat -> samples;
	int src_lines = src_mat -> lines;
	int src_bands = src_mat -> bands;

	if(cmpstr(src_mat->interleave, "bil"))
	{
		for (int i = start_row; i < end_row; i++)
		{
			for (int k = start_band; k < end_band; k++)
			{
				for (int j = start_col; j < end_col; j++)
				{
					src_index = (i * src_samples * src_bands + k * src_samples + j) * elem_size;
					dst_index = ((i - start_row) * samples * bands + (k - start_band) * samples + j - start_col) * elem_size;

					for (int t = 0; t < elem_size; t++)
						dst_data[dst_index + t] = src_data[src_index + t];					
				}
			}
		}
	}
	else if (cmpstr(src_mat->interleave, "bip"))
	{
		for (int i = start_row; i < end_row; i++)
		{
			for (int j = start_col; j < end_col; j++)
			{
				for (int k = start_band; k < end_band; k++)
				{
					src_index = (i * src_samples * src_bands + j * src_bands + k) * elem_size;
					dst_index = ((i - start_row) * samples * bands + (j - start_col) * bands + k - start_band) * elem_size;

					for (int t = 0; t < elem_size; t++)
						dst_data[dst_index + t] = src_data[src_index + t];					
				}
			}
		}
	}
	else if (cmpstr(src_mat->interleave, "bsq"))
	{
		for (int k = start_band; k < end_band; k++)
		{
			for (int i = start_row; i < end_row; i++)
			{
				for (int j = start_col; j < end_col; j++)
				{
					src_index = (k * src_samples * src_lines + i * src_samples + j) * elem_size;
					dst_index = ((k - start_band) * samples * lines + (i - start_row) * samples + j - start_col) * elem_size;

					for (int t = 0; t < elem_size; t++)
						dst_data[dst_index + t] = src_data[src_index + t];					
				}
			}
		}
	}
	else 
		printf("interleave fasle, get range ");

	if(src_mat->wavelength !=NULL)
	{
		float* start_wave = (float*)src_mat->wavelength + start_band;
		float* dst_wave = (float*)dst_mat->wavelength;

		memcpy(dst_wave, start_wave, (end_band-start_band)*sizeof(float));
	}

	return dst_mat;
}

/**
* @brief      reshape bsq hyper mat to 2d simple mat.
* @param[in]  src_mat     hyper image.
* @param[in]  dst_rows    rows of simple mat.
* @param[in]  dst_cols    cols of simple mat.
* @retval     dst_mat     simple image. 
**/
simple_mat reshape_hypermat_2_simplemat(hyper_mat src_mat, int dst_rows, int dst_cols)
{

	int src_samples = src_mat -> samples;
	int src_lines = src_mat -> lines;
	int src_bands = src_mat -> bands;

	int src_size = src_samples * src_lines * src_bands;
	int dst_size = dst_rows * dst_cols ;

	hypercv_assert(src_size == dst_size, "reshape could not change the size");

	simple_mat dst_mat = create_simple_mat(dst_rows, dst_cols, src_mat->data_type,1);

	memcpy(dst_mat->data, src_mat->data, dst_rows * dst_cols * dst_mat->elem_size);

	return dst_mat;
}

/**
* @brief      change the band data into simple mat.
* @param[in]  src_mat     hyper image.
* @param[in]  dst_mat     simple mat.
* @param[in]  band        select band.
**/
void hyper_mat_2_simple_mat(hyper_mat src_mat, simple_mat dst_mat, int band)
{
	hypercv_assert(cmpstr(src_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");
	int samples,lines;
	samples = src_mat -> samples;
	lines = src_mat -> lines;
	dst_mat -> rows = lines;
	dst_mat -> cols = samples;
	dst_mat -> data_type = src_mat -> data_type;
    
	int elemsize = get_elemsize(src_mat->data_type);
	char* data = (char*)src_mat->data+(samples*lines*(band-1)*elemsize);

	memcpy((char*)dst_mat->data,(char*)data,samples*lines*elemsize);
}


/**
* @brief      change the band data into simple mat.
* @param[in]  dst_mat     hyper mat.
* @param[in]  src_mat     simple mat.
* @param[in]  band        select band.
**/
void simple_mat_2_hyper_mat(hyper_mat dst_mat, simple_mat src_mat, int band)
{
	int samples = dst_mat->samples;
	int lines = dst_mat->lines;
	int bands = dst_mat->bands;
	hypercv_assert(src_mat->rows==lines&&src_mat->cols==samples,"simple mat size unequal to hyper mat");
	hypercv_assert(band<=bands&&band>0,"band<bands");
	hypercv_assert(cmpstr(dst_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");

	char* dst = (char*)dst_mat->data + samples*lines*(band-1);
	char* src = (char*)src_mat->data;

	memcpy(dst,src,samples*lines);
}

/**
* @brief      simple mat transport.
* @param[in]  res_mat     simple mat.
* @param[in]  src_mat     simple mat.
**/
void simple_mat_transport(simple_mat res,simple_mat src)
{
	int rows = res->rows;
	int cols = res->cols;
	
	hypercv_assert(rows == src->cols && cols == src->rows && res->data_type == src->data_type, "data size of transport image equal to srcmat ");

	int data_type = src->data_type;
	int elemsize = get_elemsize(data_type);

	char *res_data = (char*)res->data;
	char *src_data = (char*)src->data;

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<elemsize;k++)
				res_data[i*cols*elemsize+j*elemsize+k] = src_data[j*rows*elemsize+i*elemsize+k];

}

void simple_mat_addition_uchar(simple_mat mat1, simple_mat mat2, simple_mat dst_mat)
{
	hypercv_assert(mat1!=NULL&&mat2!=NULL&&dst_mat!=NULL,"input mat cannot be empty");
	hypercv_assert(mat1->channels == mat2->channels,"input mat channels error");
	
	int rows,cols;
	int channels = mat1->channels;
	
	if(mat1->rows>=mat2->rows)
		rows = mat2->rows;
	else
		rows = mat1->rows;

	if(mat1->cols>=mat2->cols)
		cols = mat2->cols;
	else
		cols = mat1->cols;

	unsigned char* data1 = (unsigned char*)mat1->data;
	unsigned char* data2 = (unsigned char*)mat2->data;
	
	unsigned char* dst_data = (unsigned char*)dst_mat->data;

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)	
			for(int k=0;k<channels;k++)
				dst_data[i*cols*channels+j*channels+k] = data1[i*cols*channels+j*channels+k]+data2[i*cols*channels+j*channels+k];

}

void simple_mat_addition_float(simple_mat mat1, simple_mat mat2, simple_mat dst_mat)
{
	hypercv_assert(mat1!=NULL&&mat2!=NULL&&dst_mat!=NULL,"input mat cannot be empty");
	hypercv_assert(mat1->channels == mat2->channels,"input mat channels error");

	int rows,cols;
	int channels = mat1->channels;
	
	if(mat1->rows>=mat2->rows)
		rows = mat2->rows;
	else
		rows = mat1->rows;

	if(mat1->cols>=mat2->cols)
		cols = mat2->cols;
	else
		cols = mat1->cols;

	float* data1 = (float*)mat1->data;
	float* data2 = (float*)mat2->data;
	float* dst_data = (float*)dst_mat->data;

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<channels;k++)
				dst_data[i*cols*channels+j*channels+k] = data1[i*cols*channels+j*channels+k]+data2[i*cols*channels+j*channels+k];

}

void simple_mat_log(simple_mat src_mat, simple_mat dst_mat)
{
	hypercv_assert(src_mat->data_type==4&&dst_mat->data_type == 4 , "input mat must be float mat");
	hypercv_assert(src_mat->rows == dst_mat->rows && src_mat->cols == dst_mat->cols, "src mat size == dst_mat size");

	int rows = src_mat->rows;
	int cols = src_mat->cols;
	
	float* src_data = (float*)src_mat->data;
	float* dst_data = (float*)dst_mat->data;

	for(int i=0;i<rows*cols;i++)
		dst_data[i] = log(src_data[i]);
}

void hyper_mat_splicing(hyper_mat mat, hyper_mat part, int start_index)
{
	hypercv_assert(mat->data_type == part->data_type,"data type error");

	int elemsize = get_elemsize(mat->data_type); 

	unsigned char* mat_data = (unsigned char*)mat->data+start_index*elemsize;
	unsigned char* part_data= (unsigned char*)part->data;

	memcpy(mat_data, part_data,part->samples*part->lines*part->bands*elemsize);
}

