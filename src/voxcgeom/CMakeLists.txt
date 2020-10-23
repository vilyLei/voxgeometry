
set(CGEOM_FILES
    # Header Files
    cgeomPre.h
    # Source Files
    )

set(MATH_FILES
    # Header Files
    math/Vec3D.h
    math/Orientation3D.h
    math/EulerAngles.h
    math/Quaternion.h
    # Source Files
    math/Vec3D.cc
    math/Orientation3D.cc
    math/EulerAngles.cc
    math/Quaternion.cc
    )

set(BASE_FILES
    # Header Files
    base/GeomBase.h
    base/Sphere.h
    base/RadialLine.h
    base/StraightLine.h
    base/LineSegment.h
    base/Plane.h
    base/Cone.h
    base/AABB.h
    # Source Files
    base/GeomBase.cc
    base/Sphere.cc
    base/RadialLine.cc
    base/StraightLine.cc
    base/LineSegment.cc
    base/Plane.cc
    base/Cone.cc
    base/AABB.cc
    )

set(CALC_FILES
    # Header Files
    calc/PlaneCalc.h
    # Source Files
    calc/PlaneCalc.cc
    )

source_group("math\\" FILES ${MATH_FILES})
source_group("base\\" FILES ${BASE_FILES})
source_group("calc\\" FILES ${CALC_FILES})


set(PROJECT_FILES
    ${CGEOM_FILES}
    ${MATH_FILES}
    ${BASE_FILES}
    ${CALC_FILES}
    )

#add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
add_library(voxcgeom STATIC ${PROJECT_FILES})