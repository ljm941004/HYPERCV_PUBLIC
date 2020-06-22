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
}STRUCT_2D;

typedef STRUCT_2D* S_2D;

/**
 * @brief	   create a 2 dimension struct use in morphology process. 
 * @param[in]  width 	    2D struct width.
 * @param[in]  height  	    2D struct height.
 * @retval     S_2D         2 dimension struct. 
 **/
S_2D create_2D_struct(int width, int height);

/**
 * @brief	   create a 2 dimension struct use in morphology process. 
 * @param[in]  width 	    2D struct width.
 * @param[in]  height  	    2D struct height.
 * @param[in]  data   	    2D struct data.
 * @retval     S_2D         2 dimension struct. 
 **/
S_2D create_2D_struct_with_data(int width, int height, void* data);

/**
 * @brief	   delete a 2 dimension struct. 
 * @param[in]  s 	    2D struct .
 **/
void delete_S_2D(S_2D s);
