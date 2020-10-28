project(Prokhorov_distance_utilities)

if(NOT CGAL_WITH_EIGEN3_VERSION VERSION_LESS 4.11.0)
  add_executable (prokhorov_distance prokhorov_distance.cpp)
  if (TBB_FOUND)
    target_link_libraries(prokhorov_distance ${TBB_LIBRARIES})
  endif(TBB_FOUND)

  #add_test(NAME Prokhorov_distance_utilities_Prokhorov_read_file
  #    COMMAND $<TARGET_FILE:prokhorov_distance>
  #    "${CMAKE_SOURCE_DIR}/data/persistence_diagram/first.pers" "${CMAKE_SOURCE_DIR}/data/persistence_diagram/second.pers")

  install(TARGETS prokhorov_distance DESTINATION bin)

endif(NOT CGAL_WITH_EIGEN3_VERSION VERSION_LESS 4.11.0)
