/*************************************************************************
	> File Name: HisEqualization.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

/**            
 * @brief      function to hisequalization 
 * @param[in]  src_mat             input mat.        
 * @param[in]  dst_mat             result mat.
**/
void HisEqualization(simple_mat src_mat, simple_mat dst_mat)
{
	_assert(src_mat!=NULL&&dst_mat!=NULL,"input mat could not be NULL");
	
	int rows = src_mat->rows;
	int cols = src_mat->cols;
	_assert(rows==dst_mat->rows&&dst_mat->cols==cols,"input mat size equal");

	unsigned char* data = (unsigned char*) src_mat ->data;
	unsigned char* dst_data = (unsigned char*) dst_mat ->data;

	hist[256] = {0};
	
	for(int i=0; i<rows*cols; i++)
		hist[*data++]+=1;
	
	for(int i=1; i<256; i++)
	{
		hist[i] += hist[i-1];
		hist[i] = hist[i]*255/(rows*cols);
	}
	
	for(int i=0; i<rows*cols; i++)
		dst_data[i] = hist[data[i]];
}
