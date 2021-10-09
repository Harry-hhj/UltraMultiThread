cmake_minimum_required(VERSION 3.21)
project(example)

set(CMAKE_CXX_STANDARD 20)  # Note that CXX14 will report an error

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}")

add_compile_options(-Wall -Werror=return-type -Wno-unused-variable)
if (CMAKE_BUILD_TYPE STREQUAL Release)
    add_compile_options(-O3 -flto -march=native)
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    add_compile_options(-O3 -flto -march=native -g)
elseif (CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
    add_compile_options(-Os -flto -march=native)
else ()
    add_compile_options(-O0 -g)
endif ()


find_package(Python 3.6 REQUIRED COMPONENTS Development Interpreter)
find_package(pybind11 REQUIRED)

include_directories(${Python_INCLUDE_DIRS})
include_directories(${pybind11_INCLUDE_DIRS})
include_directories(UltraMultiThread/include)

FILE (GLOB ALL_SOURCES "*.cpp" "*.c" )
FILE (GLOB ALL_INCLUDES "*.hpp" "*.h" )
SET (ALL_SRCS 
	 ${ALL_SOURCES}
	 ${ALL_INCLUDES}
)

add_executable(example ${ALL_SRCS})
target_link_libraries(example pthread)
target_link_libraries(example Python::Python pybind11::pybind11)