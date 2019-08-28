AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/src/" HYPERMAT_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/process/src/" HYPERMAT_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/highgui/src/" HYPERMAT_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/algorithm/src/" HYPERMAT_src)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/core/include" "${CMAKE_CURRENT_SOURCE_DIR}/process/include"  "${CMAKE_CURRENT_SOURCE_DIR}/algorithm/include")

ADD_LIBRARY(hypercv SHARED ${HYPERMAT_src})


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
endif()

find_package(GDAL)
if(GDAL_FOUND)
	ADD_DEFINITIONS(-Dgdal_switch=1)
	include_directories(${GDAL_INCLUDE_DIRS})
	target_link_libraries(hypercv gdal)
endif()



install(TARGETS hypercv DESTINATION lib)
file(GLOB hdrs "core/include/core/*.h" "process/include/process/*.h" "algorithm/include/algorithm/*.h")
install(FILES ${hdrs} DESTINATION include)
