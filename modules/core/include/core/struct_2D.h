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
	unsigned char* data;
}STRUCT_2D;

typedef STRUCT_2D* S_2D;

S_2D create_2D_struct(int width, int height);

S_2D create_2D_struct_with_data(int width, int height, unsigned char* data);
