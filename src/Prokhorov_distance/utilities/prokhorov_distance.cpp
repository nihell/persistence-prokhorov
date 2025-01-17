/*    This file is part of the Gudhi Library - https://gudhi.inria.fr/ - which is released under MIT.
 *    See file LICENSE or go to https://gudhi.inria.fr/licensing/ for full license details.
 *    Authors:       Francois Godi, small modifications by Pawel Dlotko
 *
 *    Copyright (C) 2015 Inria
 *
 *    Modification(s):
 *      - YYYY/MM Author: Description of the modification
 */

#include <gudhi/Prokhorov.h>
#include <gudhi/reader_utils.h>
#include <iostream>
#include <vector>
#include <utility>  // for pair
#include <string>
#include <limits>  // for numeric_limits

int main(int argc, char** argv) {
  if (argc < 3) {
    std::clog << "To run this program please provide as an input two files with persistence diagrams. Each file" <<
        " should contain a birth-death pair per line. Third, optional parameter is an error bound on the bottleneck" <<
        " distance (set by default to the smallest positive double value). If you set the error bound to 0, be" <<
        " aware this version is exact but expensive. The program will now terminate \n";
    return -1;
  }
  std::vector<std::pair<double, double>> diag1 = Gudhi::read_persistence_intervals_in_dimension(argv[1]);
  std::vector<std::pair<double, double>> diag2 = Gudhi::read_persistence_intervals_in_dimension(argv[2]);

  std::vector<double> coefs;
  if (argc > 3) {
    for(ssize_t i = 3; i < argc; i++){
		coefs.push_back(atof(argv[i]));
	}
  }
  double b = Gudhi::persistence_diagram::prokhorov_distance(diag1, diag2, coefs);
  std::clog << "The distance between the diagrams is : " << b << "." << std::endl;

  return 0;
}
