cmake_minimum_required(VERSION 3.29)
project(CrystalsMazeGame)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_DIR /opt/homebrew/opt/sdl2)
set(SDL2_IMAGE_DIR /opt/homebrew/opt/sdl2_image)

find_package(SDL2 REQUIRED PATHS ${SDL2_DIR})
find_package(SDL2_image REQUIRED PATHS ${SDL2_IMAGE_DIR})

include_directories(/opt/homebrew/opt/sdl2/include/SDL2)
include_directories(/opt/homebrew/opt/sdl2_image/include/SDL2)

add_executable(code src/main.cpp
        src/game.cpp
        src/game.h
)

target_link_libraries(code ${SDL2_LIBRARIES} /opt/homebrew/lib/libSDL2_image.dylib)
