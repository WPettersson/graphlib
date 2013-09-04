include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
  ${PYTHON_INCLUDE_DIRS})
add_library("graphlib-python" MODULE "graphlib.cpp")
target_link_libraries(graphlib-python "graphlib" ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
