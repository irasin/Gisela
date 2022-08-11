
set(SRC "main.cpp")
set(target "demo_opencl")

add_executable(${target})
target_sources(${target} PRIVATE ${SRC})
target_include_directories(${target} PUBLIC ${INC_DIR})

# add_definitions(-DCL_TARGET_OPENCL_VERSION=200)
# add_definitions(-DCL_HPP_TARGET_OPENCL_VERSION=200)
# add_definitions(-DCL_HPP_MINIMUM_OPENCL_VERSION=200)
find_package(OpenCL)

if(OpenCL_FOUND)
    message(STATUS "OpenCL_LIBRARIES = " ${OpenCL_LIBRARIES})
    message(STATUS "OpenCL_INCLUDE_DIRS = " ${OpenCL_INCLUDE_DIRS})
    target_link_libraries(${target} PRIVATE OpenCL::OpenCL)
else()
    set(OPENCL_HEADER
        ${THIRD_PARTY_DIR}/OpenCL-Headers
        ${THIRD_PARTY_DIR}/OpenCL-CLHPP/include
    )

    add_definitions(-DUSE_CLHPP)

    # assert opencl in cuda lib
    if(DEFINED ENV{CUDA_HOME})
        message("CUDA_HOME: $ENV{CUDA_HOME}")
    else()
        message(FATAL_ERROR "NOT DEFINED CUDA_HOME VARIABLES")
    endif()

    set(OPENCL_LIB
        $ENV{CUDA_HOME}/lib/x64 # windows
        $ENV{CUDA_HOME}/lib64 # linux
    )

    target_include_directories(${target} PRIVATE ${OPENCL_HEADER})
    target_link_directories(${target} PRIVATE ${OPENCL_LIB})
    target_link_libraries(${target} PRIVATE OpenCL)
endif()
