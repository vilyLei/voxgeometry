
set(STARA_FILES
    # Header Files
    stara/StNode.h
    stara/BinaryHeap.h
    stara/StarA.h
    # Source Files
    stara/StNode.cc
    stara/BinaryHeap.cc
    stara/StarA.cc
    )

#   set(OTHER_FILES
#       # Header Files
#       # Source Files
#       )

source_group("stara\\" FILES ${STARA_FILES})


set(PROJECT_FILES
    ${STARA_FILES}
    )

#add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
add_library(simnav STATIC ${PROJECT_FILES})