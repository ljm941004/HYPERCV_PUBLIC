/*************************************************************************
	> File Name: modules/highgui/src/precomp.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
//#include <tchar.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#ifndef gdal_switch 
#define gdal_switch 0
#endif

#if gdal_switch
#include "gdal/gdal.h"
#endif

#ifndef X11_switch
#define X11_switch 0
#endif


#ifndef use_SDL
#define use_SDL 0
#endif

#if use_SDL 
#include <SDL.h>
#include <SDL_image.h>
#endif

#if X11_switch
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif



#include "core/core.h"
#include "process/process.h"
#include "algorithm/Algorithm.h"
#include "highgui/hypercv_gui.h"

