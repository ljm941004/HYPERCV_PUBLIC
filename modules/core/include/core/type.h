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


//* @param[in]  data_type   data_type of hyper spectral image, data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer.


#define ALLOC_BYTE_ALIGNMENT 64

#define BYTE_ALIGNMENT(address, alignment) \
{ \
	(address) = (((address) + ((alignment) - 1)) & (-alignment)); \
}

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
 


