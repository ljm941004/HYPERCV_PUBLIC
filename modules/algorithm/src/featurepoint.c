/*************************************************************************
	> File Name: algorithm/src/featurepoint.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

#include "precomp.h"

feature_point feature_point_alloc(const int descriptor_dimension)
{
	feature_point f = (feature_point)malloc(sizeof(FeaturePoint));
	MALLOC_FAIL_CHECK(f);

	f->descriptor_length = descriptor_dimension;
	f->descriptor = (float*)malloc(sizeof(float)*descriptor_dimension);

	MALLOC_FAIL_CHECK(f->descriptor);
	return f;
}

void delete_feature_point(feature_point f)
{
	if(f == NULL)
		return;

	free(f->descriptor);
	f->descriptor = NULL;

	free(f);
	f = NULL;
}

