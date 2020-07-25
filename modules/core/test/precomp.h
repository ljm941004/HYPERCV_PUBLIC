#pragma once
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <gtest/gtest.h>
#include "util.hpp"
extern"C"
{
#include "c_include/hypercv_core.h"
#include "c_include/hypercv_process.h"
#include "algorithm/hypercv_algorithm.h"
}

#ifndef _cplusplus 

#define _cplusplus 
#endif

#include "cxx_include/hypercv_core.hpp"
using namespace std;
using namespace hypercv;

