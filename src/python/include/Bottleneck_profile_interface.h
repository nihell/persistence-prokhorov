/*    This file is part of the Gudhi Library - https://gudhi.inria.fr/ - which is released under MIT.
 *    See file LICENSE or go to https://gudhi.inria.fr/licensing/ for full license details.
 *    Author(s):       Vincent Rouvreau
 *
 *    Copyright (C) 2016 Inria
 *
 *    Modification(s):
 *      - YYYY/MM Author: Description of the modification
 */

#ifndef INCLUDE_BOTTLENECK_PROFILE_INTERFACE_H_
#define INCLUDE_BOTTLENECK_PROFILE_INTERFACE_H_

#include <gudhi/Bottleneck_profile.h>

#include <iostream>
#include <vector>
#include <utility>  // for std::pair

namespace Gudhi {

namespace persistence_diagram {

  // bottleneck_profile function renamed for the python function can be called bottleneck_profile  
  
  double bottleneck_prof(const std::vector<std::pair<double, double>>& diag1,
                    const std::vector<std::pair<double, double>>& diag2,
                     double t){
	return bottleneck_profile(diag1, diag2, t);					 
 }

}  // namespace persistence_diagram

}  // namespace Gudhi


#endif  // INCLUDE_BOTTLENECK_PROFILE_INTERFACE_H_
