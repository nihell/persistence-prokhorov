#include <gudhi/Bottleneck_profile.h>



#include <pybind11/numpy.h>

#include <pybind11_diagram_utils.h>

// For compatibility with older versions, we want to support e=None.
// In C++17, the recommended way is std::optional<double>.


double bottleneck_prof(Dgm d1, Dgm d2, double t){
  auto diag1 = numpy_to_range_of_pairs(d1);
  auto diag2 = numpy_to_range_of_pairs(d2);

  py::gil_scoped_release release;

  return Gudhi::persistence_diagram::bottleneck_profile(diag1, diag2, t);
}

PYBIND11_MODULE(bottleneck_prof, m) {
      m.attr("__license__") = "GPL v3";
      m.def("bottleneck_profile", &bottleneck_prof,
          py::arg("diagram_1"), py::arg("diagram_2"),
          py::arg("t")=py::none(),
          R"pbdoc(
    Compute the value of the bottleneck profile at threshold t.
    Points at infinity and on the diagonal are supported.

    :param diagram_1: The first diagram.
    :type diagram_1: numpy array of shape (m,2)
    :param diagram_2: The second diagram.
    :type diagram_2: numpy array of shape (n,2)
    :param t: double, should be >=0, argument of the bottleneck profile.
    :type e: numpy array of shape (d,1)
    :rtype: float
    :returns: the Bottleneck profile.
    )pbdoc");
}
