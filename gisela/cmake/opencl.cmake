# # generate cl code to cpp src file
include(FindPythonInterp REQUIRED)

add_custom_command(OUTPUT ${SRC_DIR}/kernel/cl/cl_src.cc
    COMMAND ${PYTHON_EXECUTABLE} ${SRC_DIR}/kernel/cl/convert_cl.py)

add_custom_target(ConvertCL ALL DEPENDS ${SRC_DIR}/kernel/cl/cl_src.cc)

# # use opencl 2.0
add_definitions(-DCL_TARGET_OPENCL_VERSION=200)
add_definitions(-DCL_HPP_TARGET_OPENCL_VERSION=200)
add_definitions(-DCL_HPP_MINIMUM_OPENCL_VERSION=200)

# # use opencl header & c++ bindings
set(OPENCL_HEADER
    ${THIRD_PARTY_DIR}/OpenCL-Headers
    ${THIRD_PARTY_DIR}/OpenCL-CLHPP/include
)

include_directories(${OPENCL_HEADER})

find_package(OpenCL)

if(OpenCL_FOUND)
    message(STATUS "OpenCL_LIBRARIES = " ${OpenCL_LIBRARIES})

# target_link_library(xxx PRIVATE ${OpenCL_LIBRARIES})
else()
    # assert opencl in cuda lib
    if(DEFINED ENV{CUDA_PATH})
        message("CUDA_PATH: $ENV{CUDA_PATH}")
    else()
        message(FATAL_ERROR "NOT DEFINED CUDA_PATH VARIABLES")
    endif()

    set(OPENCL_LIB_DIR
        $ENV{CUDA_PATH}/lib/x64 # windows
        $ENV{CUDA_PATH}/lib64 # linux
    )

    link_directories(${OPENCL_LIB_DIR})
    set(OpenCL_LIBRARIES OpenCL)
endif()
