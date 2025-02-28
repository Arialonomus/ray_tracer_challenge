# 'Google_tests' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Gather unit test source files
set(GFX_UNIT_TESTS
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/data_structures/vector3.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/data_structures/vector4.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/data_structures/color.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/data_structures/matrix3.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/data_structures/matrix4.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/functions/transform.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/functions/linear_algebra.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/surface.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/sphere.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/plane.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/cube.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/cylinder.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/cone.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/surfaces/triangle.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/object.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/composite_surface.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/bounding_box.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/ray.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/intersection.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/geometry/world.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/shading/material.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/shading/shading.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/shading/textures/texture.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/shading/textures/texture_map.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/shading/textures/procedural_textures/procedural_texture.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics/shading/textures/procedural_textures/patterns/pattern_texture.test.cpp
)
set(RAY_TRACER_UNIT_TESTS
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracer/rendering/canvas.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracer/rendering/camera.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracer/rendering/rendering.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracer/data_handling/parse.test.cpp
)

# Gather all test sources into single variable
set(TEST_SOURCES
        ${GFX_UNIT_TESTS}
        ${RAY_TRACER_UNIT_TESTS}
)

# Create the test executable
add_executable(Google_Tests_run ${TEST_SOURCES})

# Link Google Test and program libraries to the test executable
target_link_libraries(Google_Tests_run PRIVATE
        gtest
        gtest_main
        rt
)

# Ensure the correct include directories are set for tests
target_include_directories(Google_Tests_run PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/graphics
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracer
)

# Ensure Google Test headers are visible globally
target_include_directories(Google_Tests_run PRIVATE
        ${gtest_SOURCE_DIR}/include
)