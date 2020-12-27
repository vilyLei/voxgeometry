
set(MATH_FILES
    # Header Files
    math/MatrixComputer.h
    # Source Files
    math/MatrixComputer.cc
    )

set(BASE_FILES
    # Header Files
    # Source Files
    )

set(CALC_FILES
    # Header Files
    # Source Files
    )

source_group("math\\" FILES ${MATH_FILES})
source_group("base\\" FILES ${BASE_FILES})
source_group("calc\\" FILES ${CALC_FILES})


set(PROJECT_FILES
    ${MATH_FILES}
    ${BASE_FILES}
    ${CALC_FILES}
    )

#add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
add_library(demo STATIC ${PROJECT_FILES})