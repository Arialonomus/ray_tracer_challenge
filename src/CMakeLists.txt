# # # # # # # #
# GFX Library #
# # # # # # # #

# Create the gfx library
add_library(gfx)

# Set source files for the gfx library
target_sources(gfx PRIVATE
        graphics/utils/util_functions.cpp
        graphics/data_structures/vector4.cpp
        graphics/data_structures/color.cpp
        graphics/data_structures/matrix4.cpp
        graphics/functions/linear_algebra.cpp
        graphics/functions/transform.cpp
        graphics/geometry/shapes/surface.cpp
        graphics/geometry/shapes/sphere.cpp
        graphics/geometry/shapes/plane.cpp
        graphics/geometry/shapes/cube.cpp
        graphics/geometry/shapes/cylinder.cpp
        graphics/geometry/shapes/cone.cpp
        graphics/geometry/shapes/triangle.cpp
        graphics/geometry/object.cpp
        graphics/geometry/composite_surface.cpp
        graphics/geometry/bounding_box.cpp
        graphics/geometry/ray.cpp
        graphics/geometry/intersection.cpp
        graphics/geometry/world.cpp
        graphics/shading/patterns/stripe_pattern.cpp
        graphics/shading/patterns/gradient_pattern.cpp
        graphics/shading/patterns/ring_pattern.cpp
        graphics/shading/patterns/checkered_pattern.cpp
        graphics/shading/material.cpp
        graphics/shading/shading_functions.cpp
)

# Include the directories for the gfx library
target_include_directories(gfx PUBLIC
        graphics/data_structures
        graphics/functions
        graphics/geometry
        graphics/geometry/shapes
        graphics/shading
        graphics/shading/patterns
        graphics/utils
)

# Set C++ standard for the gfx library
target_compile_features(gfx PUBLIC cxx_std_23)

# # # # # # # #
# Ray Tracer  #
# # # # # # # #

# Define the library for ray tracer functions
add_library(rt)

# Set source files for the raytracer library
target_sources(rt PRIVATE
        ray_tracer/rendering/canvas.cpp
        ray_tracer/rendering/camera.cpp
        ray_tracer/rendering/rendering_functions.cpp
        ray_tracer/data_handling/parse.cpp
)
target_link_libraries(rt PUBLIC
        gfx
        nlohmann_json::nlohmann_json
)

# Include the directories for the rt library
target_include_directories(rt PUBLIC
        ray_tracer/rendering
        ray_tracer/data_handling
)

# Define the ray tracer executable and targets
add_executable(ray_tracer
        main.cpp
)
target_link_libraries(ray_tracer PRIVATE
        rt
)

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
            ${CMAKE_CURRENT_SOURCE_DIR}/graphics/data_structures
            ${CMAKE_CURRENT_SOURCE_DIR}/graphics/functions
            ${CMAKE_CURRENT_SOURCE_DIR}/graphics/utils
    )
endforeach()
