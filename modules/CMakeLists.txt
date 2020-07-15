OPTION(BUILD_SHARED_LIBS            "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)"  ON)
OPTION(BUILD_WITH_OPENCV            "Build opencv lib in hypercv"  OFF)

OPTION(BUILD_SATELLITE_MODEL "BUILD SATELLITE SIMULATION MODEL" OFF)

OPTION(BUILD_CXX  "C++ fuse c" ON)

if(BUILD_CXX)
	add_definitions(-D_cplusplus)
endif()


AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/src/c_src" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/src/cxx_src" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/process/src/" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/highgui/src/" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/algorithm/src/" HYPERCV_src)

if(BUILD_SATELLITE_MODEL)
	AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/satellite/src/" HYPERCV_src)
endif()

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/core/include/" "${CMAKE_CURRENT_SOURCE_DIR}/process/include"  "${CMAKE_CURRENT_SOURCE_DIR}/algorithm/include" "${CMAKE_CURRENT_SOURCE_DIR}/highgui/include" )
#"${CMAKE_CURRENT_SOURCE_DIR}/satellite/include")

if(BUILD_SHARED_LIBS)
	ADD_LIBRARY(hypercv SHARED ${HYPERCV_src})
else()
	ADD_LIBRARY(hypercv STATIC ${HYPERCV_src})
endif()


find_package(GTest)

if (GTest_FOUND)
	include_directories(${GTEST_INCLUDE_DIRS} )

	AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/test/" testcore_src)
	add_executable(testcore ${testcore_src})
	target_link_libraries(testcore ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(testcore hypercv)

	AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/process/test/" testprocess_src)
	add_executable(testprocess ${testprocess_src})
	target_link_libraries(testprocess ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(testprocess hypercv)

	AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/algorithm/test/" testalgorithm_src)
	add_executable(testalgorithm ${testalgorithm_src})
	target_link_libraries(testalgorithm ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(testalgorithm hypercv)

	AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/highgui/test/" testhighgui_src)
	add_executable(testhighgui ${testhighgui_src})
	target_link_libraries(testhighgui ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(testhighgui hypercv)

	#    AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/satellite/test/" testsatellite_src)
	# add_executable(testsatellite ${testsatellite_src})
	# target_link_libraries(testsatellite ${GTEST_BOTH_LIBRARIES})
	#target_link_libraries(testsatellite hypercv)
endif()

find_package(GDAL)
if(GDAL_FOUND)
	ADD_DEFINITIONS(-Dgdal_switch=1)
	include_directories(${GDAL_INCLUDE_DIRS})
	target_link_libraries(hypercv gdal)
endif()

find_package(X11)
if(X11_FOUND)
	ADD_DEFINITIONS(-DX11_switch=1)
	include_directories(${X11_INCLUDE_DIRS})
	target_link_libraries(hypercv X11)
endif()

find_package(SDL)
if(SDL_FOUND) 
	find_package(SDL_image)
	if(SDL_IMAGE_FOUND) 
		ADD_DEFINITIONS(-DUSE_SDL=1)
		include_directories(${SDL_IMAGE_INCLUDE_DIRS})
		include_directories(${SDL_INCLUDE_DIRS})
		target_link_libraries(hypercv SDL_image)
		target_link_libraries(hypercv SDL)
	endif()
endif()

if(BUILD_WITH_OPENCV)
	find_package(OpenCV)
	if(OpenCV_FOUND)
		ADD_DEFINITIONS(-Dopencv_switch=1)
		include_directories(${OPENCV_INCLUDE_DIRS})
		target_link_libraries(hypercv ${OpenCV_LIBS})
	endif()
endif()
target_link_libraries(hypercv -lpthread -lm)

install(TARGETS hypercv DESTINATION lib)
file(GLOB hdrs "core/include/c_include/*.h"   "core/include/cxx_include/*.h" "process/include/process/*.h" "algorithm/include/algorithm/*.h" "highgui/include/highgui/*.h" "satellite/include/satellite/*.h")
install(FILES ${hdrs} DESTINATION include)
