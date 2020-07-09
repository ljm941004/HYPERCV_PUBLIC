/*************************************************************************
	> File Name: modules/satellite/src/precomp.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年05月11日 星期一 21时50分08秒
 ************************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
//#include <tchar.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h> /* for size_t */
#include <errno.h>

#ifndef gdal_switch 
#define gdal_switch 0
#endif

#if gdal_switch
#include "gdal/gdal.h"
#endif

#include "c_include/hypercv_core.h"
#include "process/hypercv_process.h"
#include "algorithm/hypercv_algorithm.h"
#include "highgui/hypercv_gui.h"
#include "satellite/hypercv_satellite.h"
