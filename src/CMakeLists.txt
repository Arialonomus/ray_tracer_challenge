# # # # # # # #
# GFX Library #
# # # # # # # #

# Create the gfx library
add_library(gfx)

# Set source files for the gfx library
target_sources(gfx PRIVATE
        gfx/utils/util_functions.cpp
        gfx/data_structures/vector4.cpp
        gfx/data_structures/color.cpp
        gfx/data_structures/canvas.cpp
        gfx/data_structures/matrix2.cpp
        gfx/data_structures/matrix3.cpp
        gfx/data_structures/matrix4.cpp
        gfx/functions/transform.cpp
        gfx/geometry/ray.cpp
        gfx/geometry/sphere.cpp
        gfx/geometry/intersection.cpp
        gfx/shading/shading_functions.cpp
)

# Include the directories for the gfx library
target_include_directories(gfx PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx/data_structures
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx/functions
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx/geometry
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shading
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx/utils
)

# Set C++ standard for the gfx library
target_compile_features(gfx PUBLIC cxx_std_23)

# # # # # # # #
# Ray Tracer  #
# # # # # # # #

# Define the ray tracer executable and targets
add_executable(
        ray_tracer ray_tracer/ray_tracer.cpp
)
target_link_libraries(ray_tracer PRIVATE gfx)

# # # # # # # # # # #
# Chapter-End Demos #
# # # # # # # # # # #

# Manually define the demo executables
add_executable(
        ch_01 demos/ch_01/ch_01.cpp
)
add_executable(
        ch_02 demos/ch_02/ch_02.cpp
)
add_executable(
        ch_04 demos/ch_04/ch_04.cpp
)
add_executable(
        ch_05 demos/ch_05/ch_05.cpp
)

# List the demo targets
set(DEMO_TARGETS
        ch_01
        ch_02
        ch_04
        ch_05
)

# Apply common configurations for all demo executables
foreach(DEMO_TARGET ${DEMO_TARGETS})
    target_link_libraries(${DEMO_TARGET} PRIVATE gfx)
    target_include_directories(${DEMO_TARGET} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/gfx/data_structures
            ${CMAKE_CURRENT_SOURCE_DIR}/gfx/functions
            ${CMAKE_CURRENT_SOURCE_DIR}/gfx/utils
    )
endforeach()
