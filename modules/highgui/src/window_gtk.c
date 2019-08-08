/*************************************************************************
	> File Name: window_gtk.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include<stdio.h>

struct hypercv_window;

typedef struct hypercv_window
{
	int signature;
	char* name;

	int last_key;
	int flags;
	int status; 

}hypercv_window;









