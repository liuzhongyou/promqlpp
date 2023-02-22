cmake_minimum_required(VERSION 3.24)
project(cortex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

enable_testing()
add_subdirectory(test)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif (CCACHE_FOUND)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include)

add_compile_options(-fdiagnostics-color=always)

link_libraries(fmt)

add_executable(cortex main.cpp)
target_include_directories(cortex PRIVATE ${HEADERS})
target_compile_options(cortex PRIVATE -Wall -Wextra -Wpedantic -ggdb -lrt)
