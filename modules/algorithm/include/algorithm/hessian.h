/*************************************************************************
	> File Name: algorithm/include/algorithm/hessian.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/

typedef struct 
{
    int   width;
    int   height;
    int   filterStep;
    int   filter;
    float *responses;
    unsigned char *laplacian;
}response_layer;


HYPERCV_VECTOR_DECLARE(FPVector,feature_point);
HYPERCV_VECTOR_DECLARE(RLVector,response_layer);



typedef struct HESSIAN_MATRIX
{
	/* propeties */
    float threshold;
    int   octaveFilters;
    int   initSampleCount;
    
    /* vectors */
    FPVector* fps;
    struct RLVector *responseMap;
    
    /* intergral image */
    simple_mat intergral_image;
}hessian_matrix;
