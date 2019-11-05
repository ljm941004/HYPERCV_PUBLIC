/*************************************************************************
	> File Name: simple_mat_show.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

#if X11_switch
void smshow(const char* display_name, simple_mat mat)
{
	_assert(mat!=NULL,"show mat != NULL");

	XEvent xev;
	Visual *visual;
	XImage *ximage;
	GC gc;

	int WIDTH = mat->cols;
	int HEIGHT = mat->rows;

	unsigned char* data = (unsigned char*)mat->data;
	unsigned char* buffer=(unsigned char*)malloc(WIDTH*HEIGHT*4*sizeof(unsigned char));

	if(mat->channels == 1)
	{
		for(int i=0;i<WIDTH*HEIGHT;i++)
		{
			for(int j=0;j<3;j++)
				buffer[i*4+j]=data[i];
			buffer[i*4+3] = 1;
		}
	}
	else if(mat->channels == 3)
	{
		for(int i=0;i<WIDTH*HEIGHT;i++)
		{
			for(int j=0;j<3;j++)
				buffer[i*4+j]=data[i*3+j];

			buffer[i*4+3] = 1;
		}
	}
	else if(mat->channels == 4)
	{
		memcpy(buffer,data,WIDTH*HEIGHT*4);
	}

	char* displayname = getenv(display_name);
	Display *display = XOpenDisplay(displayname);

	int win_b_color;
	int win_w_color;
	win_b_color = BlackPixel(display, DefaultScreen(display));
	win_w_color = WhitePixel(display, DefaultScreen(display));

	Window window;
	window = XCreateSimpleWindow(display,DefaultRootWindow(display),0, 0, WIDTH, HEIGHT, 0,win_b_color, win_w_color);

	visual = DefaultVisual(display, 0);

	//XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);
	XFlush(display);
	gc = XCreateGC(display, window, 0, NULL);
	//XEvent event;
	while (1)
	{
		XPutImage (display, window, gc, ximage, 0, 0, 0, 0, WIDTH, HEIGHT);
		XFlush(display);
//todo fix bug		
	}
}

#endif






