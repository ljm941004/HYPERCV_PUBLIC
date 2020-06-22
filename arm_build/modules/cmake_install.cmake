# Install script for directory: /home/ljm/HYPERCV/modules

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ljm/HYPERCV/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ljm/HYPERCV/arm_build/bin/libhypercv.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhypercv.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhypercv.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/aarch64-linux-gnu-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhypercv.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/Algorithm.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/HisEqualization.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/cem.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/cluster.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/dft.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/normalize.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/pca.h"
    "/home/ljm/HYPERCV/modules/algorithm/include/algorithm/shapematch.h"
    "/home/ljm/HYPERCV/modules/core/include/core/core.h"
    "/home/ljm/HYPERCV/modules/core/include/core/err.h"
    "/home/ljm/HYPERCV/modules/core/include/core/hypercv.h"
    "/home/ljm/HYPERCV/modules/core/include/core/hypermat.h"
    "/home/ljm/HYPERCV/modules/core/include/core/point.h"
    "/home/ljm/HYPERCV/modules/core/include/core/simplemat.h"
    "/home/ljm/HYPERCV/modules/core/include/core/struct_2D.h"
    "/home/ljm/HYPERCV/modules/core/include/core/type.h"
    "/home/ljm/HYPERCV/modules/core/include/core/vector.h"
    "/home/ljm/HYPERCV/modules/highgui/include/highgui/draw.h"
    "/home/ljm/HYPERCV/modules/highgui/include/highgui/hypercv_gui.h"
    "/home/ljm/HYPERCV/modules/highgui/include/highgui/smshow.h"
    "/home/ljm/HYPERCV/modules/process/include/process/GeometricTransformation.h"
    "/home/ljm/HYPERCV/modules/process/include/process/RadiometricCalibration.h"
    "/home/ljm/HYPERCV/modules/process/include/process/colortransform.h"
    "/home/ljm/HYPERCV/modules/process/include/process/datatypechange.h"
    "/home/ljm/HYPERCV/modules/process/include/process/dwt.h"
    "/home/ljm/HYPERCV/modules/process/include/process/filter.h"
    "/home/ljm/HYPERCV/modules/process/include/process/gradient.h"
    "/home/ljm/HYPERCV/modules/process/include/process/hypercv_process.h"
    "/home/ljm/HYPERCV/modules/process/include/process/imageprocess.h"
    "/home/ljm/HYPERCV/modules/process/include/process/mathprocess.h"
    "/home/ljm/HYPERCV/modules/process/include/process/matrixprocess.h"
    "/home/ljm/HYPERCV/modules/process/include/process/morphology.h"
    "/home/ljm/HYPERCV/modules/process/include/process/spectralprocess.h"
    "/home/ljm/HYPERCV/modules/process/include/process/threshold.h"
    "/home/ljm/HYPERCV/modules/satellite/include/satellite/satellite.h"
    "/home/ljm/HYPERCV/modules/satellite/include/satellite/satellite_attitude.h"
    "/home/ljm/HYPERCV/modules/satellite/include/satellite/satellite_orbit.h"
    )
endif()

