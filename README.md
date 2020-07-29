# Build&rarr;It [![Build Status](https://api.travis-ci.org/AjayBrahmakshatriya/buildit.svg?branch=master)](https://travis-ci.org/AjayBrahmakshatriya/buildit)

Build&rarr;It is a type based library framework for multi-stage imperative 
programming. Build&rarr;It supports programmatically generating ASTs for an
embedded language in C++. Build&rarr;It extracts expressions and statements by
overloading the basic operators. Build&rarr;It also extracts the control flow by
repeated execution and exploration of all branches. Build&rarr;It uses static
tags to detect loops and unroll static loops. 

Build&rarr;It is a pure library framework and does not require any special
compiler support. To build the library, clone the repository, navigate to the
top-level directory and run:

```
$ cmake -DCMAKE_BUILD_TYPE=[Debug/Release] -S . -B build
$ cmake --build ./build
```

Choose `Debug` for a debug build and `Release` for an optimized build without
assertions or debugging symbols. To run the samples provided with the library
(that also serve as simple test cases), run: 

```
$ cd build
$ ctest
```

CTest will report the success or failure of each test. See
[ctest(1)](https://cmake.org/cmake/help/latest/manual/ctest.1.html) for more
details.

---

To use Build&rarr;It in your own CMake projects, you can import this repository
as a git submodule, via FetchContent, or by installing it somewhere and using
find_package. This package exports the target `buildit::buildit`. Note that
applications linking to `buildit::buildit` must have exports enabled (this
corresponds to `-rdynamic` in GCC):

```
add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE buildit::buildit)
set_target_properties(my_app PROPERTIES ENABLE_EXPORTS TRUE)
```  
