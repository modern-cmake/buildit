cmake_minimum_required(VERSION 3.16)
project(buildit VERSION 0.1.0)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_file(EXECINFO_H execinfo.h)
if (NOT EXECINFO_H)
    message(FATAL_ERROR "Can only compile with a toolchain that supports backtrace()")
endif ()

add_subdirectory(src)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(samples)
    add_subdirectory(packaging)
endif ()
