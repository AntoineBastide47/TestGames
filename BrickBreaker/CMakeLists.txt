########################################################################################################################
#                                                                                                                      #
#                                   Engine Required CMake code, Please do not modify                                   #
#                                                                                                                      #
########################################################################################################################

cmake_minimum_required(VERSION 3.29)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
add_definitions(-DGLEW_STATIC)
set(GLEW_USE_STATIC_LIBS ON)
find_package(GLEW REQUIRED)

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
  set(ENGINE_EXTENSION "dylib")
  target_link_libraries(${PROJECT_NAME} PRIVATE
      "-framework CoreFoundation"
      "-framework IOKit"
      "-framework Cocoa"
  )
elseif (LINUX)
  set(ENGINE_EXTENSION "so")
  message(WARNING "Linux build is not fully supported yet, there could be some errors.")
elseif (WIN32)
  set(ENGINE_EXTENSION "dll")
  message(WARNING "Window build is not fully supported yet, there could be some errors.")
endif ()

# Make sure the engine static library is present
file(GLOB ENGINE_LIB
    EngineInclude/*-[0-9]*.[0-9]*.[0-9]*.${ENGINE_EXTENSION}
    EngineInclude/*-[0-9]*.[0-9]*.[0-9]*.[0-9]*.${ENGINE_EXTENSION}
)
list(LENGTH ENGINE_LIB ENGINE_COUNT)
if (ENGINE_COUNT EQUAL 0)
  message(FATAL_ERROR "The Game Engine's 2D shared library (.${ENGINE_EXTENSION}) was not found in EngineInclude. Please check the installation of the engine.")
elseif (ENGINE_COUNT GREATER 1)
  message(WARNING "Multiple engine shared libraries found in EngineInclude. Ensure only one is present.")
endif ()

# Recursively get all shader files and embed the shaders into the executable
include(CMakeRC.cmake)
file(GLOB_RECURSE SHADERS ${CMAKE_SOURCE_DIR}/EngineInclude/Shaders/*)
cmrc_add_resource_library(shaders NAMESPACE engine_resources ${SHADERS})

# Link the libraries needed to make the engine run
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${ENGINE_LIB}
    GLEW::GLEW
    shaders
)

# Include the directories needed to make the engine run
target_include_directories(${PROJECT_NAME} PUBLIC EngineInclude)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(${PROJECT_NAME} PRIVATE
      -O3                     # General optimization
      -DNDEBUG                # Disable assertions
      -finline-functions      # Enable inlining
      -fomit-frame-pointer    # Free up a register
      -ffunction-sections     # Enable section-based optimization
      -fdata-sections         # Enable data section optimization
  )
  target_link_options(${PROJECT_NAME} PRIVATE -Wl,-O2)
  set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

  # Add stripping for Release builds
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GAME_DEBUG=1)
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
    add_compile_definitions(ASAN_OPTIONS="verbosity=1:halt_on_error=1:detect_leaks=1:symbolize=1")

    target_compile_definitions(${PROJECT_NAME} PUBLIC GAME_DEBUG=1)
  endif ()
endif ()

########################################################################################################################
#                                                                                                                      #
#                                           Game CMake code, modify as needed                                          #
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