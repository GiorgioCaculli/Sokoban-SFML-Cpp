cmake_minimum_required(VERSION 3.19)
project(Sokoban)

find_package(Boost COMPONENTS date_time locale log filesystem REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(Sokoban src/main.cpp src/main.hpp src/ui/Menu.cpp src/ui/Menu.hpp src/ui/gui/Application.cpp src/ui/gui/Application.hpp src/util/Logger.cpp src/util/Logger.hpp src/model/Actor.cpp src/model/Actor.hpp src/model/Player.cpp src/model/Player.hpp src/model/Movable.cpp src/model/Movable.hpp src/model/Board.cpp src/model/Board.hpp src/model/Wall.cpp src/model/Wall.hpp src/model/Platform.cpp src/model/Platform.hpp src/model/Box.cpp src/model/Box.hpp src/ui/gui/states/State_Game.cpp src/ui/gui/states/State_Game.hpp src/ui/gui/states/State.cpp src/ui/gui/states/State.hpp src/ui/gui/states/State_Menu.cpp src/ui/gui/states/State_Menu.hpp src/ui/gui/states/State_Intro.cpp src/ui/gui/states/State_Intro.hpp src/ui/gui/states/State_Pause.cpp src/ui/gui/states/State_Pause.hpp src/ui/gui/states/State_Identifiers.hpp src/ui/gui/states/State_Title.cpp src/ui/gui/states/State_Title.hpp src/ui/gui/Command.cpp src/ui/gui/Command.hpp src/ui/gui/CommandQueue.cpp src/ui/gui/CommandQueue.hpp src/ui/gui/states/State_Loading.cpp src/ui/gui/states/State_Loading.hpp src/ui/gui/Parallel_Task.cpp src/ui/gui/Parallel_Task.hpp src/ui/Category.hpp src/ui/gui/Scene_Node.cpp src/ui/gui/Scene_Node.hpp src/ui/gui/Sprite_Node.cpp src/ui/gui/Sprite_Node.hpp src/ui/Resource_Holder.hpp src/ui/Resource_Holder.inl src/ui/gui/Resource_Identifiers.hpp src/ui/gui/states/State_Stack.cpp src/ui/gui/states/State_Stack.hpp src/ui/gui/entities/Entity_Player.cpp src/ui/gui/entities/Entity_Player.hpp src/ui/gui/entities/Entity_Box.cpp src/ui/gui/entities/Entity_Box.hpp src/ui/gui/entities/Entity_Wall.cpp src/ui/gui/entities/Entity_Wall.hpp src/ui/gui/entities/Entity_Platform.cpp src/ui/gui/entities/Entity_Platform.hpp src/ui/gui/entities/Entity.cpp src/ui/gui/entities/Entity.hpp)

#

target_link_libraries(Sokoban ${Boost_LIBRARIES})

file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(Sokoban sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
