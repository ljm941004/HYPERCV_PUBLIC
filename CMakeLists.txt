cmake_minimum_required(VERSION 2.8)

project(HYPERCV CXX C)

# -----------------------------------------------------------
# include required cmake files:
# -----------------------------------------------------------

set(OUTPUTS_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUTS_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUTS_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUTS_DIR})
set(CMAKE_CXX_STANDARD 11)

set(INSTALL_PATH        "${CMAKE_CURRENT_SOURCE_DIR}/install")
set(CMAKE_INSTALL_PREFIX ${INSTALL_PATH})

OPTION(BUILD_SHARED_LIBS            "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)"  ON)

# ----------------------------------------------------------------------------
# config the output path of the library and the installation:
# ----------------------------------------------------------------------------

message("-- The output path of binary files is ${CMAKE_BINARY_DIR}/bin")

message("-- The install path is ${CMAKE_INSTALL_PREFIX}")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/test_tool)

add_subdirectory(modules)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_custom_target(
	run
	@echo "[make] testing core..."
	&
	#bin/testcore --gtest_filter=CORE.VECTOR
	#bin/testcore --gtest_filter=CORE.SMSAVE
	#bin/testcore --gtest_filter=CORE.READ_WAVELENGTH
	#bin/testcore --gtest_filter=CORE.HMREAD_WITH_HDR
	#bin/testprocess --gtest_filter=PROCESS.PYRAMIDUP
	#bin/testprocess --gtest_filter=PROCESS.CONVERT
	#bin/testprocess --gtest_filter=PROCESS.LAPLACIAN
	#bin/testprocess --gtest_filter=PROCESS.OTSU
	#bin/testprocess --gtest_filter=PROCESS.MAKEBORDER
	#bin/testprocess --gtest_filter=PROCESS.FLOAT2UCHAR
    #bin/testprocess --gtest_filter=PROCESS.FLIP
	#bin/testprocess --gtest_filter=PROCESS.MERGE
	bin/testprocess --gtest_filter=PROCESS.ROTATE
	#bin/testalgorithm --gtest_filter=ALGORITHM.DFT
	#bin/testalgorithm --gtest_filter=ALGORITHM.OTSU
	#bin/testhighgui --gtest_filter=HIGHGUI.DRAWPOINT
	#bin/testhighgui --gtest_filter=HIGHGUI.DRAWLINE
	#bin/testhighgui --gtest_filter=HIGHGUI.SMSHOW
	)
