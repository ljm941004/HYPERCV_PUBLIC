/*************************************************************************
	> File Name: algorithm/src/EdgeSignalEnergy.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

float cal_edge_signal_energy(simple_mat mat)
{
	_assert(mat!=NULL, "input mat cannot be NULL");
	_assert(mat->channels = 1,"only use in grayimage");
	_assert(mat->data_type = 1,"data_type == 1");
  
	float opt1[9] = {-1,-1,1,-1,4,-1,1,-1,-1};
	float opt2[9] = {1,-1,-1,-1,4,-1,-1,-1,1};

	for(int i=0;i<9;i++)
	{
		opt1[i] = opt1[i]/6;
		opt2[i] = opt2[i]/6;
	}

	int rows = mat->rows;
	int cols = mat->cols;

	simple_mat dst1 = create_simple_mat(rows,cols,4,1);
	simple_mat dst2 = create_simple_mat(rows,cols,4,1);
	
	hypercv_filter2D(mat,dst1,opt1,3,3,0);
	hypercv_filter2D(mat,dst2,opt2,3,3,0);

    simple_mat_addition_float(dst1,dst2,dst1);

	float* res_data = (float*)dst1->data;

	float r = 0.0;
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			r+=pow(res_data[i*cols+j],2);

	delete_simple_mat(dst1);
	delete_simple_mat(dst2);

	return r/rows/cols;
}
