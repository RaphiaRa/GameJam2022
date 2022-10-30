cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Engine)

# Find Dependencies
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(Engine 
    src/SceneNode.cpp
    src/SceneManager.cpp
    src/SdlRenderer.cpp
    src/SdlError.cpp
    src/Renderer.cpp
    src/TextureArea.cpp
    src/Sprite.cpp
    src/TileSet.cpp
    src/TileMap.cpp
    src/Input.cpp
    src/AnimatedSprite.cpp
    src/SolidRect.cpp
    )

set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
target_include_directories(
    Engine
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE src
)
target_link_libraries(Engine PRIVATE
    SDL2::SDL2
    SDL2::SDL2_image
)

if (NOT DISABLE_TESTS)
    find_package(Catch2 REQUIRED)
    add_executable(EngineTest 
        test/TestSceneNode.cpp
    )
    target_link_libraries(EngineTest PRIVATE
        Catch2::Catch2WithMain
        Engine)
endif()

