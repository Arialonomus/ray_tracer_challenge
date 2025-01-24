# 'Google_tests' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Gather unit test source files
set(UNIT_TESTS
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/data_structures/vector4.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/data_structures/color.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/data_structures/canvas.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/data_structures/matrix2.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/data_structures/matrix3.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/data_structures/matrix4.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/functions/transform.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx/geometry/ray.test.cpp
)

# Gather all test sources into single variable
set(TEST_SOURCES
        ${UNIT_TESTS}
)

# Create the test executable
add_executable(Google_Tests_run ${TEST_SOURCES})

# Link Google Test and the gfx library to the test executable
target_link_libraries(Google_Tests_run PRIVATE gtest gtest_main gfx)

# Ensure the correct include directories are set for tests
target_include_directories(Google_Tests_run PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/gfx
)

# Ensure Google Test headers are visible globally
target_include_directories(Google_Tests_run PRIVATE
        ${gtest_SOURCE_DIR}/include
)