
set(WASM_FILES
    # Header Files
    # Source Files
    transformDemo.cc
    )
set(APP_TRANS_FILES
    # Header Files
    app/trans/MatTransform.h
    # Source Files
    app/trans/MatTransform.cc
    )

source_group("app\\tans\\" FILES ${APP_TRANS_FILES})

set(PROJECT_FILES
    ${WASM_FILES}
    ${APP_TRANS_FILES}
    )

#add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
add_library(wasm STATIC ${PROJECT_FILES})