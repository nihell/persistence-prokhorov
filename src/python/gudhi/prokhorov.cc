#include <gudhi/Bottleneck.h>

#include <pybind11/numpy.h>

#include <pybind11_diagram_utils.h>

// For compatibility with older versions, we want to support e=None.
// In C++17, the recommended way is std::optional<double>.
double prokhorov(Dgm d1, Dgm d2, py::array_t<double> coefs)
{
  auto c = coefs.unchecked<1>();
  std::vector<double> coef_vector;
  for(ssize_t i =0; i < c.shape(0); i++){
    coef_vector.push_back(c(i));
  }
  // I *think* the call to request() has to be before releasing the GIL.
  auto diag1 = numpy_to_range_of_pairs(d1);
  auto diag2 = numpy_to_range_of_pairs(d2);

  py::gil_scoped_release release;

  return Gudhi::persistence_diagram::prokhorov_distance(diag1, diag2, coef_vector);
}

PYBIND11_MODULE(prokhorov, m) {
      m.attr("__license__") = "GPL v3";
      m.def("prokhorov_distance", &prokhorov,
          py::arg("diagram_1"), py::arg("diagram_2"),
          py::arg("coef"),
          R"pbdoc(
    Compute the Prokhorov distance between two diagrams.
    Points at infinity and on the diagonal are supported.

    :param diagram_1: The first diagram.
    :type diagram_1: numpy array of shape (m,2)
    :param diagram_2: The second diagram.
    :type diagram_2: numpy array of shape (n,2)
    :param coef: The coefficients of the polynomial in the Prokhorov metric. Ensure non-negative entries and zeroth entry = 0
    :type e: numpy array of shape (d,1)
    :rtype: float
    :returns: the Prokhorov distance.
    )pbdoc");
}
