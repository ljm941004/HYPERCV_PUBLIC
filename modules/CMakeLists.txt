AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/src/" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/process/src/" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/highgui/src/" HYPERCV_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/algorithm/src/" HYPERCV_src)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/core/include" "${CMAKE_CURRENT_SOURCE_DIR}/process/include"  "${CMAKE_CURRENT_SOURCE_DIR}/algorithm/include" "${CMAKE_CURRENT_SOURCE_DIR}/highgui/include")

ADD_LIBRARY(hypercv SHARED ${HYPERCV_src})
ADD_LIBRARY(hypercv_static STATIC ${HYPERCV_src})

set_target_properties(hypercv_static PROPERTIES OUTPUT_NAME "hypercv")

set_target_properties(hypercv PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(hypercv_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

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


install(TARGETS hypercv hypercv_static DESTINATION lib)
file(GLOB hdrs "core/include/core/*.h" "process/include/process/*.h" "algorithm/include/algorithm/*.h" "highgui/include/highgui/*.h")
install(FILES ${hdrs} DESTINATION include)
