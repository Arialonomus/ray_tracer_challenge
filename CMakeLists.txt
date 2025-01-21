cmake_minimum_required(VERSION 3.30)

# Set the project name and specify the C++ standard
project(ray_tracer_challenge LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++ -lc++abi)
endif()

# Define options for building components
option(BUILD_TESTS "Build unit tests" TRUE)
option(BUILD_DEMOS "Build demo programs" TRUE)

# Add subdirectories
add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
