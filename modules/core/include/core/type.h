#if gdal_switch
#pragma once
#include "gdal/gdal.h"
#endif

#if (defined _M_X64 && defined _MSC_VER && _MSC_VER >= 1400) || (__GNUC__ >= 4 && defined __x86_64__)
#  if defined WIN32
#    include <intrin.h>
#  endif
#  if defined __SSE2__ || !defined __GNUC__
#    include <emmintrin.h>
#  endif
#endif

#define ALLOC_BYTE_ALIGNMENT 64

#define BYTE_ALIGNMENT(address, alignment) \
{ \
	(address) = (((address) + ((alignment) - 1)) & (-alignment)); \
}


//* @param[in]  data_type   data_type of hyper spectral image, data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer.
static inline int get_elemsize(const int data_type)
{
	switch (data_type)
	{
		case 1:
			return sizeof(char);
			break;
		case 2:
			return sizeof(short);
			break;
		case 3:
			return sizeof(int);
			break;
		case 4:
			return sizeof(float);
			break;
		case 5:
			return sizeof(double);
			break;
		case 12:
			return sizeof(unsigned short);
			break;
		case 13:
			return sizeof(unsigned int);
			break;
		case 14:
			return sizeof(long int);
			break;
		case 15:
			return sizeof(unsigned long int);
			break;
	}
	return -1;
}

#define  BORDER_CONSTANT     0
#define  BORDER_REPLICATE    1
#define  BORDER_REFLECT      2
#define  BORDER_WRAP         3
#define  BORDER_REFLECT_101  4
#define  BORDER_DEFAULT      BORDER_REFLECT_101
#define  BORDER_ISOLATED     16

#define  NORM_INF            1
#define  NORM_L1             2
#define  NORM_L2             4
#define  NORM_MINMAX         32

/////////////////////////hypercv_round/////////////////////////////////
static inline int HYPERCV_ROUND( double value )
{
#if defined _MSC_VER && defined _M_IX86
	int t;
	__asm
	{
		fld value;
		fistp t;
	}
	return t;
#elif (defined _MSC_VER && defined _M_X64) || (defined __GNUC__ && defined __x86_64__ && defined __SSE2__ && !defined __APPLE__)
	__m128d t = _mm_set_sd( value );
	return _mm_cvtsd_si32(t);
#elif defined HAVE_LRINT || defined CV_ICC || defined __GNUC__
	return (int)lrint(value);
#else
	// while this is not IEEE754-compliant rounding, it's usually a good enough approximation
	return (int)(value + (value >= 0 ? 0.5 : -0.5));
#endif
}


/////////////////////////border_index//////////////////////////
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
static inline int hypercv_border_Interpolate(int p, int len, unsigned int border_type )
{
	_assert(len>=0,"length of src must >= 0");
	_assert(border_type == BORDER_REFLECT
			||border_type == BORDER_REFLECT_101
			||border_type == BORDER_REPLICATE
			||border_type == BORDER_WRAP
			||border_type == BORDER_CONSTANT ,"Unknown/unsupported border type" );

	int index = p;

	if((unsigned)index < (unsigned)len )
		return index;

	switch(border_type)
	{
		case BORDER_REPLICATE:
			{	index = index < 0 ? 0 : len - 1;
				break;
			}
		case BORDER_REFLECT:
		case BORDER_REFLECT_101:
			{	
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
			}
		case BORDER_WRAP:
			{
				if( index < 0 )
				index -= ((index-len+1)/len)*len;
				if( index >= len )
					index %= len;
				break;
			}
		case BORDER_CONSTANT:
			{
				index = 1;
				break;
			}
	}
	return index;
}



/////////////// saturate_cast ///////////////////

static unsigned char saturate_cast_float2uchar(float value)
{

	if(value>255)
		return 255;

	int ivalue =  HYPERCV_ROUND(value);
	return (unsigned char)ivalue;
}
