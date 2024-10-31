cmake_minimum_required(VERSION 3.29)
project(2D_GAME)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Add the headers directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/Engine/include)

# Find the GameEngineLib dylib file
file(GLOB GAME_ENGINE_LIB "${CMAKE_SOURCE_DIR}/Engine/${ENGINE_LIB_PATTERN}")
if (NOT GAME_ENGINE_LIB)
    message(FATAL_ERROR "No GameEngineLib dylib found in ${GAME_ENGINE_LIB}")
endif()

# Add the main.cpp file to build the 2D_GAME executable
add_executable(2D_GAME main.cpp)

# Define paths to the static versions of GLEW and GLFW libraries
set(GLEW_STATIC_LIB /opt/homebrew/opt/glew/lib/libGLEW.a)
set(GLFW_STATIC_LIB /opt/homebrew/opt/glfw/lib/libglfw3.a)

# Link OpenGL, GLEW, and GLFW static libraries to GameEngineLib
target_link_libraries(2D_GAME PRIVATE
        ${GAME_ENGINE_LIB}
        OpenGL::GL
        ${GLEW_STATIC_LIB}
        ${GLFW_STATIC_LIB}
        "-framework CoreFoundation"
        "-framework IOKit"
        "-framework Cocoa"
)