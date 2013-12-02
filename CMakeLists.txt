cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11")
set(PACKAGE_NAME "graphlib")
set(BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include/${PACKAGE_NAME})

add_subdirectory(src)
add_subdirectory(tools)

#find_package(Boost 1.45.0 COMPONENTS python)
#find_package(PythonLibs)
#if(Boost_FOUND AND PYTHONLIBS_FOUND)
#  add_subdirectory(python)
#endif()
