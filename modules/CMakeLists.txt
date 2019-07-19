AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/src/" HYPERMAT_src)
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/process/src/" HYPERMAT_src)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/core/include" "${CMAKE_CURRENT_SOURCE_DIR}/process/include")

ADD_LIBRARY(hypercv SHARED ${HYPERMAT_src})


find_package(GTest)

if (GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})

    AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/core/test/" testcore_src)
    add_executable(testcore ${testcore_src})
    target_link_libraries(testcore ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(testcore hypercv)

    AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/process/test/" testprocess_src)
    add_executable(testprocess ${testprocess_src})
    target_link_libraries(testprocess ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(testprocess hypercv)
endif()
