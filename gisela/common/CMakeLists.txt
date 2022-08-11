

set(UTIL_LIB "util")
file(GLOB_RECURSE UTIL_SRC "util/*.cc")

add_library(${UTIL_LIB})

target_sources(${UTIL_LIB} PRIVATE ${UTIL_SRC})
target_include_directories(${UTIL_LIB} PRIVATE ${GISELA_ROOT_DIR})
