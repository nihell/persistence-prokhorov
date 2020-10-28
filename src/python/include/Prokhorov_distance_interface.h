/*    This file is part of the Gudhi Library - https://gudhi.inria.fr/ - which is released under MIT.
 *    See file LICENSE or go to https://gudhi.inria.fr/licensing/ for full license details.
 *    Author(s):       Vincent Rouvreau
 *
 *    Copyright (C) 2016 Inria
 *
 *    Modification(s):
 *      - YYYY/MM Author: Description of the modification
 */

#ifndef INCLUDE_PROKHOROV_DISTANCE_INTERFACE_H_
#define INCLUDE_PROKHOROV_DISTANCE_INTERFACE_H_

#include <gudhi/Bottleneck.h>

#include <iostream>
#include <vector>
#include <utility>  // for std::pair

namespace Gudhi {

namespace persistence_diagram {

  // prokhorov_distance function renamed for the python function can be called bottleneck_distance  
  double prokhorov(const std::vector<std::pair<double, double>>& diag1,
                    const std::vector<std::pair<double, double>>& diag2,
                     const std::vector<double>& coefs) {
    return prokhorov_distance(diag1, diag2, coefs);
  }

}  // namespace persistence_diagram

}  // namespace Gudhi


#endif  // INCLUDE_PROKHOROV_DISTANCE_INTERFACE_H_
