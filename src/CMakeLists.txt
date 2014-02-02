add_library("graphlib" SHARED "graph.cpp" "edge.cpp" "pathiterator.cpp"
  "step.cpp" "cycle.cpp" "cyclefill.cpp" "path.cpp" "twofactor.cpp")
set( HEADERS "graph.h" "edge.h" "pathiterator.h" "step.h" "cycle.h"
  "cyclefill.h" "path.h" "twofactor.h")

install(TARGETS graphlib
  LIBRARY DESTINATION ${LIBDIR}
)

install(FILES ${HEADERS}
  DESTINATION ${INCLUDEDIR}
)
