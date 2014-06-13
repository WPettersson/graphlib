SET(PROGS do_path do_end do_cycles do_cycles_b do_cycles_c do_cycles_b3 do_cycles_c3 do_cycles_d3 do_cycles_e3 do_cycles_f3 do_cycles_g3 do_circ do_twofactor do_twofactor_triangle do_cycles_kirkman do_lots_threes do_twofactor_J do_path_333)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
FOREACH(PROG ${PROGS})
  ADD_EXECUTABLE(${PROG} "${PROG}.cpp")
  TARGET_LINK_LIBRARIES(${PROG} "graphlib")
ENDFOREACH(PROG)
