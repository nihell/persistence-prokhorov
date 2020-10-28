/*    This file is part of the Gudhi Library - https://gudhi.inria.fr/ - which is released under MIT.
 *    See file LICENSE or go to https://gudhi.inria.fr/licensing/ for full license details.
 *    Author:       Francois Godi
 *
 *    Copyright (C) 2015 Inria
 *
 *    Modification(s):
 *      - 2019/06 Vincent Rouvreau : Fix doxygen warning.
 *      - 2019/08 Vincent Rouvreau: Fix issue #10 for CGAL
 *      - YYYY/MM Author: Description of the modification
 */

#ifndef PROKHOROV_H_
#define PROKHOROV_H_

#include <gudhi/Graph_matching.h>

#include <CGAL/version.h>  // for CGAL_VERSION_NR

#include <vector>
#include <algorithm>  // for max
#include <limits>  // for numeric_limits

#include <cmath>
#include <cfloat>  // FLT_EVAL_METHOD

// Make compilation fail - required for external projects - https://github.com/GUDHI/gudhi-devel/issues/10
#if CGAL_VERSION_NR < 1041101000
# error prokhorov_distance is only available for CGAL >= 4.11
#endif

namespace Gudhi {

namespace persistence_diagram {



inline double prokhorov_distance_exact(Persistence_graph& g, std::vector<double> coefs) {
  std::vector<double> sd = g.sorted_distances();
  long lower_bound_i = 0;
  long upper_bound_i = sd.size() - 1;
  const double alpha = std::pow(g.size(), 1. / 5.);
  Graph_matching m(g);
  Graph_matching biggest_unperfect(g);
  while (lower_bound_i != upper_bound_i) {
    long step = lower_bound_i + static_cast<long> ((upper_bound_i - lower_bound_i - 1) / alpha);
    m.set_r(sd.at(step));
    while (m.multi_augment()) {}  // compute a maximum matching (in the graph corresponding to the current r)
    double fr = 0;
    for (ssize_t i = 0; i< coefs.size(); i++){
    	fr += coefs[i]*std::pow(sd.at(step),i);
    }
    if (m.number_unmatched()<=fr) {
      m = biggest_unperfect;
      upper_bound_i = step;
    } else {
      biggest_unperfect = m;
      lower_bound_i = step + 1;
    }
  }
  return sd.at(lower_bound_i);
}


template<typename Persistence_diagram1, typename Persistence_diagram2>
double prokhorov_distance(const Persistence_diagram1 &diag1, const Persistence_diagram2 &diag2,
                           std::vector<double> coefs) {
  Persistence_graph g(diag1, diag2, (std::numeric_limits<double>::min)());
  if (g.bottleneck_alive() == std::numeric_limits<double>::infinity())
    return std::numeric_limits<double>::infinity();
  return (std::max)(g.bottleneck_alive(), prokhorov_distance_exact(g,coefs));
}

}  // namespace persistence_diagram

}  // namespace Gudhi

#endif  // PROKHOROV_H_
