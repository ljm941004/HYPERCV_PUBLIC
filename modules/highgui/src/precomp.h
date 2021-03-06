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

#ifndef USE_SDL
#define USE_SDL 0
#endif

#if USE_SDL 
#include <SDL.h>
#include <SDL_image.h>
#endif

#if X11_switch
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif


#include "c_include/hypercv_core.h"
#include "c_include/hypercv_process.h"
#include "algorithm/hypercv_algorithm.h"
#include "highgui/hypercv_gui.h"

