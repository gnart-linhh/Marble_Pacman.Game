cmake_minimum_required(VERSION 3.29)
project(CrystalsMazeGame)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_DIR /opt/homebrew/opt/sdl2)
set(SDL2_IMAGE_DIR /opt/homebrew/opt/sdl2_image)
set(SDL2_TTF_DIR /opt/homebrew/opt/sdl2_ttf)
set(SDL2_MIXER_DIR /opt/homebrew/opt/sdl2_mixer)

find_package(SDL2 REQUIRED PATHS ${SDL2_DIR})
find_package(SDL2_image REQUIRED PATHS ${SDL2_IMAGE_DIR})
find_package(SDL2_ttf REQUIRED PATHS ${SDL2_TTF_DIR})
find_package(SDL2_mixer REQUIRED PATHS ${SDL2_MIXER_DIR})
include_directories(${SDL2_MIXER_DIR}/include/SDL2)

include_directories(/opt/homebrew/opt/sdl2/include/SDL2)
include_directories(/opt/homebrew/opt/sdl2_image/include/SDL2)
include_directories(${SDL2_TTF_DIR}/include/SDL2)

add_executable(CrystalsMazeGame src/main.cpp
        src/game.cpp
        src/Map.cpp
        src/TextManager.cpp
)

target_link_libraries(CrystalsMazeGame
        ${SDL2_LIBRARIES}
        /opt/homebrew/lib/libSDL2_image.dylib
        /opt/homebrew/lib/libSDL2_ttf.dylib
        /opt/homebrew/lib/libSDL2_mixer.dylib
)

