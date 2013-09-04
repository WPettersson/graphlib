#include <boost/python.hpp>

#include "graph.h"
#include "step.h"
#include "path.h"
#include "cyclefill.h"
#include "cycle.h"

BOOST_PYTHON_MODULE(graphlib)
{
  using namespace boost::python;
  class_<Graph>("Graph", init<int, std::string>())
    .def("addEdge", &Graph::addEdge)
    .def("addEdgeRange", &Graph::addEdgeRange)
    .def("finish", &Graph::finish)
    .def("run", &Graph::run)
    .def("setCallback", &Graph::setCallback)
    .def("setCheckpoint", &Graph::setCheckpoint)
    .def("__repr__", &Graph::toString)
    .def("writeAsy", &Graph::writeAsy)
    .def("writeTxt", &Graph::writeTxt)
    .def("addStep", &Graph::addStep);

  //class_<Path>("Path" no_init);
  //class_<Path, bases<Step> >("Path", init<Graph *, std::vector<int>, int, std::vector<int>, 
  //    std::vector<int>, int>);

//  class_<Cycle, bases<Step> >("Cycle", init<Graph *, std::vector<int>, int, int, int>);
//
//  class_<CycleFill, bases<Step> >("CycleFill", init<Graph *, std::vector<int>,
//      std::vector<int> int, bool>);
    
}
