
set(SRC
    ${SRC_DIR}/kernel/cl/cl_src.cc
    main.cpp
)

set(target "demo_opencl")

add_executable(${target})
target_sources(${target} PRIVATE ${SRC})
target_link_libraries(${target} PRIVATE ${OpenCL_LIBRARIES})
