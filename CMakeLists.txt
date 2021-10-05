cmake_minimum_required(VERSION 3.19)
project(Sokoban)

find_package(Boost COMPONENTS date_time locale log REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(Sokoban src/main.cpp src/main.hpp src/ui/menu.cpp src/ui/menu.hpp src/ui/gui/main_frame.cpp src/ui/gui/main_frame.hpp src/util/logger.cpp src/util/logger.hpp src/ui/gui/scene_node.cpp src/ui/gui/scene_node.hpp src/ui/gui/sprite_node.cpp src/ui/gui/sprite_node.hpp src/ui/gui/actor/entity.cpp src/ui/gui/actor/entity.hpp src/ui/gui/actor/User.cpp src/ui/gui/actor/User.hpp src/ui/gui/resource_holder.hpp src/ui/gui/resource_identifiers.hpp src/ui/gui/actor/world.cpp src/ui/gui/actor/world.hpp src/model/Actor.cpp src/model/Actor.hpp src/model/Player.cpp src/model/Player.hpp src/model/Movable.cpp src/model/Movable.hpp src/model/Board.cpp src/model/Board.hpp src/model/Wall.cpp src/model/Wall.hpp src/model/Platform.cpp src/model/Platform.hpp src/model/Box.cpp src/model/Box.hpp)

#

target_link_libraries(Sokoban ${Boost_LIBRARIES})

file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(Sokoban sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
