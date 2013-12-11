add_executable("do_path" "do_path.cpp")
target_link_libraries("do_path" "graphlib")

add_executable("do_end" "do_end.cpp")
target_link_libraries("do_end" "graphlib")

add_executable("do_cycles" "do_cycles.cpp")
target_link_libraries("do_cycles" "graphlib")

add_executable("do_cycles_b" "do_cycles_b.cpp")
target_link_libraries("do_cycles_b" "graphlib")

add_executable("do_circ" "do_circ.cpp")
target_link_libraries("do_circ" "graphlib")

add_executable("do_twofactor" "do_twofactor.cpp")
target_link_libraries("do_twofactor" "graphlib")

add_executable("do_twofactor_triangle" "do_twofactor_triangle.cpp")
target_link_libraries("do_twofactor_triangle" "graphlib")

add_executable("do_cycles_kirkman" "do_cycles_kirkman.cpp")
target_link_libraries("do_cycles_kirkman" "graphlib")

include_directories("${CMAKE_SOURCE_DIR}/src")
