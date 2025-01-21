# Create the gfx library
add_library(gfx)

# Set source files for the gfx library
target_sources(gfx PRIVATE
        gfx/vector4.cpp
        gfx/color.cpp
)

# Include the directories for the gfx library
target_include_directories(gfx PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Set C++ standard for the gfx library
target_compile_features(gfx PUBLIC cxx_std_23)

# Build demo executables
#if (BUILD_DEMOS)
#    # List of demo subdirectories
#    set(DEMO_DIRS
#            demos/ch_01
#    )
#
#    # Add executables for each demo
#    foreach(DEMO_DIR ${DEMO_DIRS})
#        get_filename_component(DEMO_NAME ${DEMO_DIR} NAME)
#        add_executable(${DEMO_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${DEMO_DIR}/${DEMO_NAME}.cpp)
#        target_link_libraries(${DEMO_NAME} PRIVATE gfx)
#        target_include_directories(${DEMO_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gfx)
#    endforeach()
#endif()
