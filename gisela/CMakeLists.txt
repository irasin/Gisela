cmake_minimum_required(VERSION 3.20.0)

project(gisela VERSION 0.1.0 LANGUAGES CXX)

include(CheckCXXCompilerFlag)

if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "use CXX_STD_20")
    set(CMAKE_CXX_STANDARD 20)
elseif("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "use CXX_STD_17")
    set(CMAKE_CXX_STANDARD 17)
else()
    message(STATUS "use CXX_STD_14")
    set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_C_STANDARD 99)



set(GISELA_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR ${GISELA_ROOT_DIR}/src)
set(INC_DIR ${GISELA_ROOT_DIR}/include)
set(TEST_DIR ${GISELA_ROOT_DIR}/test)
set(CMAKE_DIR ${GISELA_ROOT_DIR}/cmake)
set(THIRD_PARTY_DIR ${GISELA_ROOT_DIR}/third_party)


include(${CMAKE_DIR}/common.cmake)

add_subdirectory(src)
