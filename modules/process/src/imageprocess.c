#include "precomp.h"

/**
* @brief      transform bil to bsq.
* @param[in]  bil_mat    bil image.
* @retval     bsq_mat    bsq image.
**/
hyper_mat bil2bsq(hyper_mat bil_mat)
{
	_assert(bil_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bil_mat -> interleave,"bsq") == 1)
		return bil_mat;

	_assert(cmpstr(bil_mat -> interleave,"bil") == 1, "input hyper mat's interleave must be bil");

	int samples   = bil_mat -> samples;
	int lines     = bil_mat -> lines;
	int bands     = bil_mat -> bands;
	int elem_size = get_elemsize(bil_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 's';
	interleave[2] = 'q';

	hyper_mat bsq_mat = create_hyper_mat(samples, lines, bands, bil_mat->data_type, interleave);

	char* bil_data = (char*)bil_mat -> data;
	char* bsq_data = (char*)bsq_mat -> data;

	int bil_index = 0, bsq_index = 0;
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
	return bsq_mat;
}

/**
* @brief      transform bil to bip.
* @param[in]  bil_mat    bil image.
* @retval     bip_mat    bip image. 
**/
hyper_mat bil2bip(hyper_mat bil_mat)
{
	_assert(bil_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bil_mat -> interleave,"bip") == 1)
		return bil_mat;

	_assert(cmpstr(bil_mat -> interleave,"bil") == 1, "input hyper mat's interleave must be bil");

	int samples   = bil_mat -> samples;
	int lines     = bil_mat -> lines;
	int bands     = bil_mat -> bands;
	int elem_size = get_elemsize(bil_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 'i';
	interleave[2] = 'p';

	hyper_mat bip_mat = create_hyper_mat(samples, lines, bands, bil_mat->data_type, interleave);

	char* bil_data = (char*)bil_mat -> data;
	char* bip_data = (char*)bip_mat -> data;

	int bil_index = 0, bip_index = 0;

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
	return bip_mat;
}

/**
* @brief      transform bsq to bil.
* @param[in]  bil_mat    bsq image.
* @retval     bip_mat    bil image. 
**/
hyper_mat bsq2bil(hyper_mat bsq_mat)
{
	_assert(bsq_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bsq_mat -> interleave,"bil") == 1)
		return bsq_mat;

	_assert(cmpstr(bsq_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");

	int samples   = bsq_mat -> samples;
	int lines     = bsq_mat -> lines;
	int bands     = bsq_mat -> bands;
	int elem_size = get_elemsize(bsq_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 'i';
	interleave[2] = 'l';

	hyper_mat bil_mat = create_hyper_mat(samples, lines, bands, bsq_mat->data_type, interleave);

	char* bsq_data = (char*)bsq_mat -> data;
	char* bil_data = (char*)bil_mat -> data;

	int bsq_index = 0, bil_index = 0;

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
	return bil_mat;
}

/**
* @brief      transform bsq to bip.
* @param[in]  bil_mat    bsq image.
* @retval     bip_mat    bip image. 
**/
hyper_mat bsq2bip(hyper_mat bsq_mat)
{
	_assert(bsq_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bsq_mat -> interleave,"bip") == 1)
		return bsq_mat;

	_assert(cmpstr(bsq_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");

	int samples   = bsq_mat -> samples;
	int lines     = bsq_mat -> lines;
	int bands     = bsq_mat -> bands;
	int elem_size = get_elemsize(bsq_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 'i';
	interleave[2] = 'p';

	hyper_mat bip_mat = create_hyper_mat(samples, lines, bands, bsq_mat->data_type, interleave);

	char* bsq_data = (char*)bsq_mat -> data;
	char* bip_data = (char*)bip_mat -> data;

	int bsq_index = 0, bip_index = 0;

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
	return bip_mat;
}

/**
* @brief      transform bip to bsp.
* @param[in]  bil_mat    bip image.
* @retval     bip_mat    bsq image. 
**/
hyper_mat bip2bsq(hyper_mat bip_mat)
{
	_assert(bip_mat != NULL,                "hyper_mat can not be NULL");

	if(cmpstr(bip_mat -> interleave,"bsq") == 1)
		return bip_mat;

	_assert(cmpstr(bip_mat -> interleave,"bip") == 1, "input hyper mat's interleave must be bip");

	int samples   = bip_mat -> samples;
	int lines     = bip_mat -> lines;
	int bands     = bip_mat -> bands;
	int elem_size = get_elemsize(bip_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 's';
	interleave[2] = 'q';

	hyper_mat bsq_mat = create_hyper_mat(samples, lines, bands, bip_mat->data_type, interleave);

	char* bip_data = (char*)bip_mat -> data;
	char* bsq_data = (char*)bsq_mat -> data;

	int bsq_index = 0, bip_index = 0;

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
	return bsq_mat;
}

/**
* @brief      transform bip to bil .
* @param[in]  bip_mat    bip image.
* @retval     bil_mat    bil image. 
**/
hyper_mat bip2bil(hyper_mat bip_mat)
{
	_assert(bip_mat != NULL,                "hyper_mat can not be NULL");
	if(cmpstr(bip_mat -> interleave,"bil") == 1)
		return bip_mat;
	_assert(cmpstr(bip_mat -> interleave,"bip") == 1, "input hyper mat's interleave must be bip");

	int samples   = bip_mat -> samples;
	int lines     = bip_mat -> lines;
	int bands     = bip_mat -> bands;
	int elem_size = get_elemsize(bip_mat->data_type);

	char interleave[3];
	interleave[0] = 'b';
	interleave[1] = 'i';
	interleave[2] = 'l';

	hyper_mat bil_mat = create_hyper_mat(samples, lines, bands, bip_mat->data_type, interleave);

	char* bip_data = (char*)bip_mat -> data;
	char* bil_data = (char*)bil_mat -> data;

	int bil_index = 0, bip_index = 0;

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
	_assert(start_col<end_col && start_row<end_row && start_band<end_band, "start col & start row & start band must < end col & end row & end band");

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

	_assert(src_size == dst_size, "reshape could not change the size");

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
	_assert(cmpstr(src_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");
	int samples,lines;
	samples = src_mat -> samples;
	lines = src_mat -> lines;
	dst_mat -> rows = lines;
	dst_mat -> cols = samples;
	dst_mat -> data_type = src_mat -> data_type;
    
	int elemsize = get_elemsize(src_mat->data_type);
	char* data = src_mat->data+(samples*lines*(band-1)*elemsize);

	memcpy(dst_mat->data,(void*)data,samples*lines*elemsize);
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
	_assert(src_mat->rows==lines&&src_mat->cols==samples,"simple mat size unequal to hyper mat");
	_assert(band<=bands&&band>0,"band<bands");
	_assert(cmpstr(dst_mat -> interleave,"bsq") == 1, "input hyper mat's interleave must be bsq");

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
	
	_assert(rows == src->cols && cols == src->rows && res->data_type == src->data_type, "data size of transport image equal to srcmat ");

	int data_type = src->data_type;
	int elemsize = get_elemsize(data_type);

	char *res_data = (char*)res->data;
	char *src_data = (char*)src->data;

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<elemsize;k++)
				res_data[i*cols*elemsize+j*elemsize+k] = src_data[j*rows*elemsize+i*elemsize+k];

}

