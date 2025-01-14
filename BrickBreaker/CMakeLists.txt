########################################################################################################################
#                                                                                                                      #
#                                   Engine Required CMake code, Please do not modify                                   #
#                                                                                                                      #
########################################################################################################################

cmake_minimum_required(VERSION 3.29)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

# Include cpptrace to be able to print stack traces
include(FetchContent)
FetchContent_Declare(
    cpptrace
    GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
    GIT_TAG v0.7.3 # <HASH or TAG>
)
FetchContent_MakeAvailable(cpptrace)

# Add the main.cpp file to build the SpaceInvaders executable
add_executable(${PROJECT_NAME} main.cpp
    GameCode/BrickBreaker.cpp
    GameCode/BrickBreaker.h
    GameCode/GameLevel.cpp
    GameCode/GameLevel.h
    GameCode/Brick.cpp
    GameCode/Brick.h
    GameCode/Paddle.cpp
    GameCode/Paddle.h
    GameCode/Ball.cpp
    GameCode/Ball.h
)

# Depending on the OS of the user, link the libraries correctly and find the engine library
if (APPLE)
  file(GLOB ENGINE_LIB EngineFiles/[a-zA-Z0-9]*-[0-9]*.[0-9]*.[0-9]*.a)
  target_link_libraries(${PROJECT_NAME} PRIVATE
      "-framework CoreFoundation"
      "-framework IOKit"
      "-framework Cocoa"
  )
elseif (Unix)
  message(STATUS "Linux build is not fully supported yet, there could be some errors.")
elseif (WIN32)
  message(STATUS "Window build is not fully supported yet, there could be some errors.")
else ()
  message(STATUS "Unknown operating system, please configure the library linking.")
endif ()

# Make sure the engine static library is present
if (NOT ENGINE_LIB)
  message(FATAL_ERROR "The Game Engine's 2D static library was not found in the folder EngineFiles. Make sure you built the engine using `make build` in the engine's file location before creating your project.")
endif ()

# Link the libraries needed to make the engine run
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${ENGINE_LIB}
    OpenGL::GL
    glfw
    GLEW::GLEW
    glm::glm
    shaders
    cpptrace::cpptrace
)

# Embed the shaders into the executable
include(CMakeRC.cmake)
file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/EngineFiles/Shaders/*)
cmrc_add_resource_library(shaders NAMESPACE engine_resources ${SHADER_FILES})

# Include the directories needed to make the engine run
target_include_directories(${PROJECT_NAME} PRIVATE
    EngineFiles
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${cpptrace_SOURCE_DIR}/include
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(${PROJECT_NAME} PRIVATE
      -O3                     # General optimization
      -DNDEBUG                # Disable assertions
      -finline-functions      # Enable inlining
      -flto                   # Link-Time Optimization
      -fomit-frame-pointer    # Free up a register
      -ffunction-sections     # Enable section-based optimization
      -fdata-sections         # Enable data section optimization
  )
  target_link_options(${PROJECT_NAME} PRIVATE
      -Wl,-O2                 # Optimize linker
  )
  set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

  # Add stripping for Release builds
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    # Enable AddressSanitizer and retain frame pointers for better stack traces
    set(SANITIZER_FLAGS "-fsanitize=address -fno-omit-frame-pointer")

    # Enable additional debugging features
    set(EXTRA_DEBUG_FLAGS "-g -O1")  # Generate debug symbols with minimal optimization
    set(ASAN_OPTIONS_FLAGS "-fsanitize-recover=address -fsanitize=undefined -fsanitize-address-use-after-scope")

    # Combine flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS} ${EXTRA_DEBUG_FLAGS} ${ASAN_OPTIONS_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS} ${EXTRA_DEBUG_FLAGS} ${ASAN_OPTIONS_FLAGS}")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${SANITIZER_FLAGS} ${EXTRA_DEBUG_FLAGS} ${ASAN_OPTIONS_FLAGS}")

    # Pass runtime options for AddressSanitizer via environment variables
    add_compile_definitions(
        ASAN_OPTIONS="verbosity=1:halt_on_error=1:detect_leaks=1:symbolize=1"
    )
  endif ()
endif ()

########################################################################################################################
#                                                                                                                      #
#                                         Project CMake code, modify as needed                                         #
#                                                                                                                      #
########################################################################################################################

# Embed the assets into the executable
file(GLOB_RECURSE ASSET_FILES ${CMAKE_SOURCE_DIR}/Assets/*)
cmrc_add_resource_library(assets NAMESPACE resources ${ASSET_FILES})

# Link user libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    assets
)

# Include user include directories
target_include_directories(${PROJECT_NAME} PUBLIC

)