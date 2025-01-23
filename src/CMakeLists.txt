# Create the gfx library
add_library(gfx)

# Set source files for the gfx library
target_sources(gfx PRIVATE
        gfx/vector4.cpp
        gfx/color.cpp
        gfx/canvas.cpp
        gfx/matrix2.cpp
        gfx/matrix3.cpp
        gfx/matrix4.cpp
)

# Include the directories for the gfx library
target_include_directories(gfx PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Set C++ standard for the gfx library
target_compile_features(gfx PUBLIC cxx_std_23)

# Manually define the demo executables
add_executable(
        ch_01 demos/ch_01/ch_01.cpp
)
add_executable(
        ch_02 demos/ch_02/ch_02.cpp
)

# List the demo targets
set(DEMO_TARGETS
        ch_01
        ch_02
)

# Apply common configurations for all demo executables
foreach(DEMO_TARGET ${DEMO_TARGETS})
    target_link_libraries(${DEMO_TARGET} PRIVATE gfx)
    target_include_directories(${DEMO_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gfx)
endforeach()

