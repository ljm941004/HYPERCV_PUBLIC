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

#define gdal_switch 0

#if gdal_switch
#include "gdal/gdal.h"
#include "gdal/gdal_priv.h"
#endif


extern"C"
{
#include "core/core.h"
#include "process/process.h"
#include "algorithm/Algorithm.h"
}
