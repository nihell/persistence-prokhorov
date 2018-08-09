# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  # starting from cmake 3.9 the usage of DOXYGEN_EXECUTABLE is deprecated
  if(TARGET Doxygen::doxygen)
    get_property(DOXYGEN_EXECUTABLE TARGET Doxygen::doxygen PROPERTY IMPORTED_LOCATION)
  endif()

  add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${GUDHI_USER_VERSION_DIR}/Doxyfile
                    WORKING_DIRECTORY ${GUDHI_USER_VERSION_DIR}
                    COMMENT "Generating API documentation with Doxygen in ${GUDHI_USER_VERSION_DIR}/doc/html/" VERBATIM)

  if(TARGET user_version)
    # In dev version, doxygen target depends on user_version target. Not existing in user version
    add_dependencies(doxygen user_version)
  endif()
endif(DOXYGEN_FOUND)
