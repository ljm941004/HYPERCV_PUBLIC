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

#include "core/core.h"
#include "process/process.h"
#include "algorithm/Algorithm.h"
#include "highgui/hypercv_gui.h"
