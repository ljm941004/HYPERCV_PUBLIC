/*************************************************************************
	> File Name: sobelprocess.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

// default sobel ksize == 3 ,todo fix other ksize 

/**            
 * @brief      find border correspondence index
 * @param[in]  p                   index.        
 * @param[in]  len                 len of src_mat.
 * @param[in]  border_type         type of border.
 * @retva      hyper_mat           hyper mat 
 * Various border types, image boundaries are denoted with '|'
 * BORDER_CONSTANT    = 0, //!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`
 * BORDER_REPLICATE   = 1, //!< `aaaaaa|abcdefgh|hhhhhhh`
 * BORDER_REFLECT     = 2, //!< `fedcba|abcdefgh|hgfedcb`
 * BORDER_WRAP        = 3, //!< `cdefgh|abcdefgh|abcdefg`
 * BORDER_REFLECT_101 = 4, //!< `gfedcb|abcdefgh|gfedcba`
 * BORDER_DEFAULT     = BORDER_REFLECT_101, //!< same as BORDER_REFLECT_101
 * BORDER_ISOLATED    = 16 //!< do not look outside of ROI
 **/
static int hypercv_border_Interpolate(int p, int len, unsigned int border_type )
{
	_assert(len>=0,"length of src must >= 0");
	_assert(border_type == BORDER_REFLECT
			||border_type == BORDER_REFLECT_101
			||border_type == BORDER_REPLICATE
			||border_type == BORDER_WRAP
			||border_type == BORDER_CONSTANT ,"Unknown/unsupported border type" );

	int index = p;

	if( (unsigned)index < (unsigned)len )
		return index;

	switch(border_type)
	{
		case BORDER_REPLICATE:
			index = index < 0 ? 0 : len - 1;
			break;

		case BORDER_REFLECT:
		case BORDER_REFLECT_101:
			if( len == 1 )
				return 0;
			int delta = border_type == BORDER_REFLECT_101;
			do
			{
				if( index < 0 )
					index = -index - 1 + delta;
				else
					index = len - 1 - (index - len) - delta;
			}
			while( (unsigned)index >= (unsigned)len );
			break;

		case BORDER_WRAP:
			if( index < 0 )
				index -= ((index-len+1)/len)*len;
			if( index >= len )
				index %= len;
			break;

		case BORDER_CONSTANT:
			index = -1;
			break;
	}
	return index;
}


/**            
 * @brief      sobel kernel to blur image.
 * @param[in]  src                 simple mat.        
 * @param[in]  dst                 dst mat.
 * @param[in]  threshold           threshold of blur.
 * @param[in]  border_type         type of border.
 **/
void hypercv_sobel(simple_mat src, simple_mat dst, int threshold, int border_type)
{
	_assert(src->rows == dst->rows&&src->cols==dst->cols, "src size == dst size");
	_assert(border_type == BORDER_REFLECT
			||border_type == BORDER_REFLECT_101
			||border_type == BORDER_REPLICATE
			||border_type == BORDER_WRAP
			||border_type == BORDER_CONSTANT ,"Unknown/unsupported border type" );
	_assert(src->channels == 1,"sobel image channels == 1")

	int rows = src->rows;
	int cols = src->cols;

	int gradx = 0;
	int grady = 0;
	int pix;

	int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int gy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};

	int index_m,index_n;

	unsigned char* src_data = src->data;
	unsigned char* dst_data = dst->data;

	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			gradx = 0;
			grady = 0;

			for(int m=0; m<3; m++)
			{
				for(int n=0; n<3; n++)
				{
					if((i+m-1<0)||i+m-1>=rows)
						index_m = hypercv_border_Interpolate(i+m-1,rows,border_type);
					else
						index_m = i+m-1;

					if(j+n-1<0||j+n>cols)
						index_n = hypercv_border_Interpolate(j+n-1,cols,border_type);
					else
						index_n = j+n-1;

					gradx += gx[m][n]*src_data[index_m*cols+index_n];
					grady += gy[m][n]*src_data[index_m*cols+index_n];
				}
			}
        gradx = abs(gradx);
        grady = abs(grady);
		pix = gradx>grady?gradx:grady;
		dst_data[i*cols+j]=pix>threshold?255:0;
		}
	}
}
