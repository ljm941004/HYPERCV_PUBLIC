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

set(INSTALL_PATH        "${CMAKE_CURRENT_SOURCE_DIR}/installation")
set(CMAKE_INSTALL_PREFIX ${INSTALL_PATH})

OPTION(BUILD_SHARED_LIBS            "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)"  ON)
OPTION(BUILD_TESTS                  "Build accuracy & regression tests"                                   ON)

# ----------------------------------------------------------------------------
# config the output path of the library and the installation:
# ----------------------------------------------------------------------------


#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Output directory for application")
#set(LIB_OUTPUT_PATH         ${CMAKE_BINARY_DIR}/lib)
#set(INCLUDE_INSTALL_PATH    "${CMAKE_CURRENT_SOURCE_DIR}/installation/include")
#set(CONFIG_INSTALL_PATH     "${CMAKE_CURRENT_SOURCE_DIR}/installation/include")
#set(RUNTIME_INSTALL_PATH    "${CMAKE_CURRENT_SOURCE_DIR}/installation/bin")

message("-- The output path of binary files is ${CMAKE_BINARY_DIR}/bin")

add_subdirectory(modules)

message("-- The install path is ${CMAKE_INSTALL_PREFIX}")


add_custom_target(
    run
    @echo "[make] testing core..."
    &
    bin/testcore --gtest_filter=haha.hss
)
