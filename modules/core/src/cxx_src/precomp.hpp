#ifndef __HYPERCV_CORE_PRECOMP_H__
#define __HYPERCV_CORE_PRECOMP_H__

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef gdal_switch 
#define gdal_switch 0
#endif


extern "C"
{
#include "c_include/hypercv_core.h"
#include "c_include/hypercv_process.h"
#include "algorithm/hypercv_algorithm.h"
#include "highgui/hypercv_gui.h"
}

#include "cxx_include/hypercv_core.hpp"

using namespace std;

#endif
