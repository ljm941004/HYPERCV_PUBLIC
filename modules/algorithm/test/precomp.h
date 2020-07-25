/*************************************************************************
	> File Name: precomp.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <gtest/gtest.h>
#include "util.hpp"

#if gdal_switch
#include "gdal/gdal.h"
#include "gdal/gdal_priv.h"
#endif

extern"C"
{
#include "c_include/hypercv_core.h"
#include "c_include/hypercv_process.h"
#include "algorithm/hypercv_algorithm.h"
#include "highgui/hypercv_gui.h"
}
