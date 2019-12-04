/*************************************************************************
	> File Name: algorithm/include/algorithm/featurepoint.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

typedef struct 
{
	float x;
	float y;
	float response;
	float orientation;
	int   laplacian;
	int   descriptor_length;
	float *descriptor;
}FeaturePoint;
typedef FeaturePoint* feature_point;


feature_point feature_point_alloc(const int descriptor_dimension);

void delete_feature_point(feature_point f);








