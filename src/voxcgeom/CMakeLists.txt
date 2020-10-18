
set(CGEOM_FILES
    # Header Files
    cgeomPre.h
    # Source Files
    )
set(BASE_FILES
    # Header Files
    base/Vec3D.h
    # Source Files
    base/Vec3D.cc)

source_group("base\\" FILES ${BASE_FILES})


set(PROJECT_FILES
    ${CGEOM_FILES}
    ${BASE_FILES})

#add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
add_library(voxcgeom STATIC ${PROJECT_FILES})