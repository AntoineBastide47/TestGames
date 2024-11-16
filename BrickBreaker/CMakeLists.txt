cmake_minimum_required(VERSION 3.29)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLM REQUIRED glm)

# Include CMakeRC
include(CMakeRC.cmake)

file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/EngineFiles/Shaders/*)
cmrc_add_resource_library(shaders NAMESPACE engine_resources ${SHADER_FILES})

file(GLOB_RECURSE ASSET_FILES ${CMAKE_SOURCE_DIR}/Assets/*)
cmrc_add_resource_library(assets NAMESPACE resources ${ASSET_FILES})

# Include cpptrace to be able to print stack traces
include(FetchContent)
FetchContent_Declare(
    cpptrace
    GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
    GIT_TAG        9269a72c54e0faab981aa8710b65858e2eb1f59c # <HASH or TAG>
)
FetchContent_MakeAvailable(cpptrace)

# Find the GameEngineLib dylib file
file(GLOB GAME_ENGINE_LIB EngineFiles/GameEngineLib-[0-9]*.[0-9]*.[0-9]*.a)
if (NOT GAME_ENGINE_LIB)
  message(FATAL_ERROR "No GameEngineLib static library found in ${GAME_ENGINE_LIB}")
endif ()

# Create a custom target that depends on assets.h
add_custom_target(AssetsHeader DEPENDS ${CMAKE_BINARY_DIR}/assets.h)

# Add the main.cpp file to build the SpaceInvaders executable
add_executable(${PROJECT_NAME} main.cpp
    Game/BrickBreaker.cpp
    Game/BrickBreaker.h
    Game/GameLevel.cpp
    Game/GameLevel.h
    Game/Brick.cpp
    Game/Brick.h
    Game/Player.cpp
    Game/Player.h
)

# Link OpenGL, GLEW, and GLFW static libraries to GameEngineLib
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GAME_ENGINE_LIB}
    OpenGL::GL
    /opt/homebrew/opt/glew/lib/libGLEW.a
    /opt/homebrew/opt/glfw/lib/libglfw3.a
    /opt/homebrew/opt/glm/lib/libglm.dylib
    "-framework CoreFoundation"
    "-framework IOKit"
    "-framework Cocoa"
    shaders
    cpptrace::cpptrace
    assets
)

target_include_directories(${PROJECT_NAME} PRIVATE
    EngineFiles
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)