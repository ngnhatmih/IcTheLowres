cmake_minimum_required(VERSION 3.21)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# project name
project(ICTL VERSION "0.0.1")

# Bring assets to build directory
set(ASSETS ${PROJECT_SOURCE_DIR}/assets)
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

# Set the executable file for the project
set(SOURCE_FILES
	src/main_menu.cpp
	src/game.cpp
	src/input.cpp
	src/sudoku.cpp 
	src/vector2d.cpp
	src/play.cpp
	src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Make sure submodules exist before building
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/vendor/sdl/CMakeLists.txt")
	message(FATAL_ERROR "Unable to locate the SDL3 submodule in filesystem. Try running `git submodule update --init --recursive`.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/vendor/sdl_image/CMakeLists.txt")
	message(FATAL_ERROR "Unable to locate the SDL3 submodule in filesystem. Try running `git submodule update --init --recursive`.")
endif()

# No need to build tests when bulding SDL
option(SDL_TEST OFF)

# Build the submodules along with the project
add_subdirectory(vendor/sdl)
add_subdirectory(vendor/sdl_image)

# Force minimum compatability to be with C++14
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

# Add includes for the project
target_include_directories(
	${PROJECT_NAME} PRIVATE include
	${PROJECT_NAME} PRIVATE vendor/sdl/include
	${PROJECT_NAME} PRIVATE vendor/sdl_image/include
)

# Add and link libraries to project
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Enable lto on the target if supported (in Release mode)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
endif()

# Enable PIE/PIC on the target if supported
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE True)