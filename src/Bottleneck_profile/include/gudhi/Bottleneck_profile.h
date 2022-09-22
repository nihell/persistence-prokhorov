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

#ifndef BOTTLENECKPROFILE_H_
#define BOTTLENECKPROFILE_H_

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

inline double bottleneck_profile_exact(Persistence_graph& g, double t){
	Graph_matching m(g);
	Graph_matching biggest_unperfect(g);
	m.set_r(t);
	while (m.multi_augment()) {}  // compute a maximum matching (in the graph corresponding to the current r)
	return m.number_unmatched();
}

template<typename Persistence_diagram1, typename Persistence_diagram2>
double bottleneck_profile(const Persistence_diagram1 &diag1, const Persistence_diagram2 &diag2,
                           double t) {
  Persistence_graph g(diag1, diag2, (std::numeric_limits<double>::min)());
  if (g.bottleneck_alive() == std::numeric_limits<double>::infinity())
    return std::numeric_limits<double>::infinity();
  return bottleneck_profile_exact(g,t);
}

}  // namespace persistence_diagram

}  // namespace Gudhi

#endif  // BOTTLENECKPROFILE_H_
