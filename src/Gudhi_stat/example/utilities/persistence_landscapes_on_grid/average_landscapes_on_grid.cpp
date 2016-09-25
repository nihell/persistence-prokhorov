/*    This file is part of the Gudhi Library. The Gudhi library
 *    (Geometric Understanding in Higher Dimensions) is a generic C++
 *    library for computational topology.
 *
 *    Author(s):       Pawel Dlotko
 *
 *    Copyright (C) 2015  INRIA Sophia-Saclay (France)
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <gudhi/abstract_classes/Abs_Topological_data.h>
#include <gudhi/concretizations/Persistence_landscape_on_grid.h>



using namespace Gudhi;
using namespace Gudhi::Gudhi_stat;

#include <iostream>


int main( int argc , char** argv )
{
	std::cout << "This program computes average persistence landscape on grid of persistence landscapes on grid created based on persistence diagrams provided as an input. Please call this program with the names of files with persistence diagrams \n";
	std::vector< const char* > filenames;
	
	if ( argc == 1 )
	{
		std::cout << "No input files given, the program will now terminate \n";
		return 1;
	}
	
	for ( int i = 1 ; i < argc ; ++i )
	{
		filenames.push_back( argv[i] );
	}
	
	std::cout << "Creating persistence landscapes...\n";
	std::vector< Abs_Topological_data_with_averages* > lands;
	for ( size_t i = 0 ; i != filenames.size() ; ++i )
	{
		Persistence_landscape_on_grid* l = new Persistence_landscape_on_grid;
		l->load_landscape_from_file( filenames[i] );
		lands.push_back( (Abs_Topological_data_with_averages*)l );
	}
	
	Persistence_landscape_on_grid av;
	av.compute_average( lands );
	
	av.print_to_file( "average.g_land" );
	
	for ( size_t i = 0 ; i != filenames.size() ; ++i )
	{
		delete lands[i];
	}
	
	std::cout << "Done \n";

	return 0;
}
