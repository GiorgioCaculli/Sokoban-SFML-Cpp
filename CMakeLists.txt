cmake_minimum_required(VERSION 3.19)
project(Sokoban)

find_package(Boost COMPONENTS date_time locale log REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(Sokoban src/main.cpp src/main.hpp src/core/actor.cpp src/core/actor.hpp src/core/wall.cpp src/core/wall.hpp src/core/player.cpp src/core/player.hpp src/core/box.cpp src/core/box.hpp src/core/platform.cpp src/core/platform.hpp src/ui/menu.cpp src/ui/menu.hpp src/ui/gui/main_frame.cpp src/ui/gui/main_frame.hpp src/util/logger.cpp src/util/logger.hpp src/core/board.cpp src/core/board.hpp)

target_link_libraries(Sokoban ${Boost_LIBRARIES})

file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(Sokoban sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
