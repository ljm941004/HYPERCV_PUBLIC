project(HYPER_MAT CXX C)

cmake_minimum_required(VERSION 2.8)

set(OUTPUTS_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUTS_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUTS_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUTS_DIR})
set(CMAKE_CXX_STANDARD 11)


add_subdirectory(modules)

add_custom_target(
    run
    @echo "[make] testing core..."
    &
    bin/testcore --gtest_filter=haha.hss
)
