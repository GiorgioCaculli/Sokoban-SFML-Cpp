cmake_minimum_required(VERSION 3.19)
project(Sokoban)

find_package(Boost COMPONENTS date_time locale log REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(Sokoban src/main.cpp src/main.hpp src/core/actor.cpp src/core/actor.hpp src/core/wall.cpp src/core/wall.hpp src/core/player.cpp src/core/player.hpp src/core/box.cpp src/core/box.hpp src/core/platform.cpp src/core/platform.hpp src/ui/menu.cpp src/ui/menu.hpp src/ui/gui/main_frame.cpp src/ui/gui/main_frame.hpp src/util/logger.cpp src/util/logger.hpp)

target_link_libraries(Sokoban ${Boost_LIBRARIES})
target_link_libraries(Sokoban glfw)
target_link_libraries(Sokoban OpenGL::GL)
