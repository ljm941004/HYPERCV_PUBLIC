/*************************************************************************
	> File Name: 2D_struct.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
// in this .h will declare a struct using in corrosion an expansion
// also using in other algorithm.
//

typedef struct
{
	int width;
	int height;
	void* data;
}2D_STRUCT

typedef 2D_STRUCT* 2D_S;

2D_S create_2D_struct(int width, int height);

2D_S create_2D_struct_with_data(int width, int height, void* data);
