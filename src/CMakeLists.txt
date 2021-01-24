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

IF(NOT PROGType)

include_directories ("${PROJECT_SOURCE_DIR}/voxcgeom")
add_subdirectory (voxcgeom)
set (EXTRA_LIBS ${EXTRA_LIBS} voxcgeom)

include_directories ("${PROJECT_SOURCE_DIR}/demo")
add_subdirectory (demo)
set (EXTRA_LIBS ${EXTRA_LIBS} demo)

include_directories ("${PROJECT_SOURCE_DIR}/wasm")
add_subdirectory (wasm)
set (EXTRA_LIBS ${EXTRA_LIBS} wasm)

include_directories ("${PROJECT_SOURCE_DIR}/simnav")
add_subdirectory (simnav)
set (EXTRA_LIBS ${EXTRA_LIBS} simnav)

# add the executable
add_executable(voxcgeometry voxcgeom.cc)
#target_link_libraries (voxcgeometry voxcgeom)
target_link_libraries (voxcgeometry ${EXTRA_LIBS})

# add the executable
add_executable(voxwasm wasm/transformDemo.cc)
target_link_libraries (voxwasm ${EXTRA_LIBS})


ELSE(NOT PROGType)

set (EXTRA_LIBS ${EXTRA_LIBS} voxcg)

# add the executable
add_executable(voxcgw voxcg.cc)


# for C and c++ compiler parameters
macro (add_compiler_flag flag)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" CACHE STRING "" FORCE)
endmacro ()

# for C++ compiler parameters
macro (add_cxx_compiler_flag flag)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" CACHE STRING "" FORCE)
endmacro ()

# for C compiler parameters
macro (add_c_compiler_flag flag)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}" CACHE STRING "" FORCE)
endmacro ()

# Adds $flag to the link flags for $target.
function (add_link_flag flags)
    unset(target_link_flags)
    get_target_property(target_link_flags voxcgw LINK_FLAGS)

    if (target_link_flags)
        unset(link_flag_found)
        string(FIND "${target_link_flags}" "${flags}" link_flag_found)

        if (NOT ${link_flag_found} EQUAL -1)
          return()
        endif ()

        set(target_link_flags "${target_link_flags} ${flags}")
    else ()
        set(target_link_flags "${flags}")
    endif ()

    set_target_properties(voxcgw PROPERTIES LINK_FLAGS ${target_link_flags})
endfunction ()

add_definitions(-DWASM_DEV_ENV)
#add_compiler_flag("-D WASM_DEV_ENV")
add_link_flag("--bind")
add_link_flag("-s WASM=1")

set(CGEOM_FILES
# Header Files
./voxcgeom/cgeomPre.h
./voxcgeom/math/Vec3D.h
./voxcgeom/math/Matrix4.h
./voxcgeom/math/Matrix4Container.h
./simnav/stara/StNode.h
./simnav/stara/BinaryHeap.h
./simnav/stara/StarA.h

./demo/math/MatrixComputer.h
./wasm/app/trans/MatTransform.h
# Source Files
./voxcgeom/cgeomPre.cc
./voxcgeom/math/Vec3D.cc
./voxcgeom/math/Matrix4.cc
./voxcgeom/math/Matrix4Container.cc
./simnav/stara/StNode.cc
./simnav/stara/BinaryHeap.cc
./simnav/stara/StarA.cc

./demo/math/MatrixComputer.cc
./wasm/app/trans/MatTransform.cc
)
set(PROJECT_FILES
    ${CGEOM_FILES}
    )
add_library(voxcg STATIC ${PROJECT_FILES})
# DPROGType is the cmake command condition parameter: -DPROGType=ON or -DPROGType=OFF
#
target_link_libraries (voxcgw ${EXTRA_LIBS})

ENDIF(NOT PROGType)
