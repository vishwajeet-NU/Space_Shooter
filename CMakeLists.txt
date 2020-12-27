cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Shooter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" "${Shooter_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} src)

add_executable(Shooter src/main.cpp src/renderer.cpp src/game.cpp src/base.cpp src/controller.cpp src/player.cpp src/boss_enemy.cpp src/enemy.cpp src/bullet.cpp src/move.cpp src/create_bullets.cpp src/collison.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(Shooter ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
