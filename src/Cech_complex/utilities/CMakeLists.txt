if (NOT CGAL_WITH_EIGEN3_VERSION VERSION_LESS 5.0.1)
  project(Cech_complex_utilities)

  if (TARGET Boost::program_options)
    add_executable(cech_persistence cech_persistence.cpp)
    target_link_libraries(cech_persistence Boost::program_options)

    if (TBB_FOUND)
      target_link_libraries(cech_persistence ${TBB_LIBRARIES})
    endif()

    add_test(NAME Cech_complex_utility_from_rips_on_tore_3D COMMAND $<TARGET_FILE:cech_persistence>
        "${CMAKE_SOURCE_DIR}/data/points/tore3D_300.off" "-r" "0.25" "-m" "0.5" "-d" "3" "-p" "3")

    install(TARGETS cech_persistence DESTINATION bin)
  endif()
endif()
