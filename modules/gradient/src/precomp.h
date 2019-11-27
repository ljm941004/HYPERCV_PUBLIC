#include <stdio.h>
#include <stdlib.h>
//#include <tchar.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "core/core.h"
#include "process/process.h"
#include "algorithm/Algorithm.h"
#include "highgui/hypercv_gui.h"
#include "gradient/gradient.h"


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
