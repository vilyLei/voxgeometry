
set(CGEOM_FILES
    # Header Files
    cgeomPre.h
    # Source Files
    )
set(BASE_FILES
    # Header Files
    base/Vec3D.h
    base/GeomBase.h
    base/Sphere.h
    base/RadialLine.h
    base/StraightLine.h
    base/LineSegment.h
    base/Plane.h
    base/AABB.h
    # Source Files
    base/Vec3D.cc
    base/GeomBase.cc
    base/Sphere.cc
    base/RadialLine.cc
    base/StraightLine.cc
    base/LineSegment.cc
    base/Plane.cc
    base/AABB.cc
    )

set(CALC_FILES
    # Header Files
    calc/PlaneCalc.h
    # Source Files
    calc/PlaneCalc.cc
    )

source_group("base\\" FILES ${BASE_FILES})
source_group("calc\\" FILES ${CALC_FILES})


set(PROJECT_FILES
    ${CGEOM_FILES}
    ${BASE_FILES}
    ${CALC_FILES}
    )

#add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
add_library(voxcgeom STATIC ${PROJECT_FILES})