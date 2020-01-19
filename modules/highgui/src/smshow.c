/*************************************************************************
	> File Name: simple_mat_show.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

//todo fix color bug
void smshow(const char* display_name, simple_mat mat)
{
	_assert(mat!=NULL,"show mat != NULL");
#if USE_SDL

	Uint32 flags = SDL_SWSURFACE;
	//SDL_Init(flags);
	SDL_Surface *screen, *image;
	int depth,done,dirty;
	SDL_Event event;
	SDL_Rect src = {0, 0, 0, 0};

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)<0)
	{
		fprintf(stderr, "couldn't initialize SDL: %s\n", SDL_GetError());
		return ;
	}

	int image_depth = get_elemsize(mat->data_type)*mat->channels*8;
	int pitch = mat->cols * mat->channels*get_elemsize(mat->data_type);

	image = SDL_CreateRGBSurfaceFrom((void*)mat->data, mat->cols, mat->rows, image_depth, pitch , 0x000000ff,0x0000ff00,0x00ff0000,0);
	//image = IMG_Load(display_name);
//	printf("%d\n");
	if(image == NULL)
	{
		printf("Couldn't convert Mat to Surface.");
		return;
	}
	
	src.w = image->w;
	src.h = image->h;

	depth = SDL_VideoModeOK(src.w, src.h, 32, SDL_SWSURFACE);
	/* Use the deepest native mode, except that we emulate 32bpp
	   for viewing non-indexed images on 8bpp screens */
	
	if (depth == 0)
	{
		if (image->format->BytesPerPixel > 1)
			depth = 32;
		else
			depth = 8;
	} 
	else if ((image->format->BytesPerPixel > 1) && (depth == 8))
		depth = 32;

	if (depth == 8)
		flags |= SDL_HWPALETTE;

	SDL_SetAlpha(image, 0, 255);

 	screen = SDL_SetVideoMode(src.w, src.h, depth, flags);


	if (screen == NULL)
	{
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
				src.w, src.h, depth, SDL_GetError());
		return;
	}

	/* Set the palette, if one exists */
	if (image->format->palette) 
		SDL_SetColors(screen, image->format->palette->colors,0, image->format->palette->ncolors);

	/* Display the image */

	done = 0;

	while (!done)
	{
		if(dirty)
		{
		SDL_BlitSurface(image, &src, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		dirty =0;
		}
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_VIDEORESIZE:
					done = 1;
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{

						case SDLK_ESCAPE:
							done = 1;
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (event.motion.state & SDL_BUTTON(1))	
						dirty = 1;
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		} 
		else
		{
			SDL_Delay(10);
		}
	}
	SDL_FreeSurface(image);
	SDL_FreeSurface(screen);
	SDL_Quit();
	return;

#elif X11_switch
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
#endif
}







