cmake_minimum_required (VERSION 2.6)
project (voxcgeometry)
# The version number.
set (VOXCGEOMTRY_VERSION_MAJOR 1)
set (VOXCGEOMTRY_VERSION_MINOR 0)
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/voxcgeomConfig.h.in"
  "${PROJECT_BINARY_DIR}/voxcgeomConfig.h"
  )

# add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")

include_directories ("${PROJECT_SOURCE_DIR}/voxcgeom")
add_subdirectory (voxcgeom)
set (EXTRA_LIBS ${EXTRA_LIBS} voxcgeom)

include_directories ("${PROJECT_SOURCE_DIR}/demo")
add_subdirectory (demo)
set (EXTRA_LIBS ${EXTRA_LIBS} demo)


include_directories ("${PROJECT_SOURCE_DIR}/wasm")
add_subdirectory (wasm)
set (EXTRA_LIBS ${EXTRA_LIBS} wasm)

# add the executable
add_executable(voxcgeometry voxcgeom.cc)
#target_link_libraries (voxcgeometry voxcgeom)
target_link_libraries (voxcgeometry ${EXTRA_LIBS})


# add the executable
add_executable(voxwasm wasm/transformDemo.cc)
target_link_libraries (voxwasm ${EXTRA_LIBS})
