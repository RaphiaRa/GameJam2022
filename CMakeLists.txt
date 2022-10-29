cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DISABLE_SOURCE_CHANGES_ON)
set(CMAKE_DISABLE_IN_SOURCE_BULD_ON)

# Extra warnings, treat warnings as error
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  set(CXX_FILESYSTEM_LIBRARIES stdc++fs)
else()
  set(CXX_FILESYSTEM_LIBRARIES)
endif()

add_subdirectory(lib/engine)
add_subdirectory(external/Lyra)
add_executable(Game
  src/main.cpp #
  src/Game.cpp #
  src/Input.cpp #
  src/Assets.cpp #
  src/MainScene.cpp #
  src/World.cpp #
  src/Character.cpp #
  src/Room.cpp #
)

target_link_libraries(Game 
  Engine 
  bfg::lyra)
