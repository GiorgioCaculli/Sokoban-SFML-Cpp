cmake_minimum_required(VERSION 3.19)
project(Sokoban)

find_package(Boost COMPONENTS date_time locale log filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(include)

set(CMAKE_CXX_STANDARD 11)

add_executable(Sokoban src/main.cpp src/main.hpp src/ui/Menu.cpp src/ui/Menu.hpp src/ui/gui/Application.cpp src/ui/gui/Application.hpp src/ui/gui/states/State_Game.cpp src/ui/gui/states/State_Game.hpp src/ui/gui/states/State.cpp src/ui/gui/states/State.hpp src/ui/gui/states/State_Menu.cpp src/ui/gui/states/State_Menu.hpp src/ui/gui/states/State_Pause.cpp src/ui/gui/states/State_Pause.hpp src/ui/gui/states/State_Identifiers.hpp src/ui/gui/states/State_Title.cpp src/ui/gui/states/State_Title.hpp src/ui/Category.hpp src/ui/gui/Scene_Node.cpp src/ui/gui/Scene_Node.hpp src/ui/gui/Sprite_Node.cpp src/ui/gui/Sprite_Node.hpp src/ui/Resource_Holder.hpp src/ui/Resource_Holder.inl src/ui/gui/Resource_Identifiers.hpp src/ui/gui/states/State_Stack.cpp src/ui/gui/states/State_Stack.hpp src/ui/gui/entities/Entity_Player.cpp src/ui/gui/entities/Entity_Player.hpp src/ui/gui/entities/Entity_Box.cpp src/ui/gui/entities/Entity_Box.hpp src/ui/gui/entities/Entity_Wall.cpp src/ui/gui/entities/Entity_Wall.hpp src/ui/gui/entities/Entity_Platform.cpp src/ui/gui/entities/Entity_Platform.hpp src/ui/gui/entities/Entity.cpp src/ui/gui/entities/Entity.hpp src/ui/Utility.inl src/ui/gui/Utility.cpp src/ui/gui/Utility.hpp src/ui/gui/World.cpp src/ui/gui/World.hpp src/ui/gui/entities/Entity_Movable.cpp src/ui/gui/entities/Entity_Movable.hpp src/ui/gui/Music_Player.cpp src/ui/gui/Music_Player.hpp src/ui/gui/Sound_Player.cpp src/ui/gui/Sound_Player.hpp src/ui/gui/Sound_Node.cpp src/ui/gui/Sound_Node.hpp src/ui/gui/states/State_Settings.cpp src/ui/gui/states/State_Settings.hpp src/ui/gui/components/Component.cpp src/ui/gui/components/Component.hpp src/ui/gui/components/Button.cpp src/ui/gui/components/Button.hpp src/ui/gui/components/Container.cpp src/ui/gui/components/Container.hpp src/ui/gui/Animation.cpp src/ui/gui/Animation.hpp src/ui/gui/components/Label.cpp src/ui/gui/components/Label.hpp)

file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    include_directories(include/sfml-windows)
    find_library(SFML_SYSTEM sfml-system libs/sfml-windows/lib)
    find_library(SFML_WINDOW sfml-window libs/sfml-windows/lib)
    find_library(SFML_GRAPHICS sfml-graphics libs/sfml-windows/lib)
    find_library(SFML_NETWORK sfml-network libs/sfml-windows/lib)
    find_library(SFML_AUDIO sfml-audio libs/sfml-windows/lib)
    target_link_libraries(Sokoban sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
endif(WIN32)

if(UNIX AND NOT APPLE)
    include_directories(include/sfml-unix)
    find_library(SFML_SYSTEM sfml-system libs/sfml-unix/lib)
    find_library(SFML_WINDOW sfml-window libs/sfml-unix/lib)
    find_library(SFML_GRAPHICS sfml-graphics libs/sfml-unix/lib)
    find_library(SFML_NETWORK sfml-network libs/sfml-unix/lib)
    find_library(SFML_AUDIO sfml-audio libs/sfml-unix/lib)
    find_library(UTIL_LOGGER util_logger libs/util-linux)
    find_library(UTIL_SERIALIZE util_serialize libs/util-linux)
    find_library(SOKOBAN_LINUX sokoban_core libs/sokoban-linux)
    target_link_libraries(Sokoban sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    target_link_libraries(Sokoban ${SOKOBAN_LINUX} ${UTIL_LOGGER} ${UTIL_SERIALIZE} ${Boost_LIBRARIES})
endif(UNIX AND NOT APPLE)

if(APPLE)
    include_directories(include/sfml-macos)
    find_library(SFML_SYSTEM sfml-system libs/sfml-macos/lib)
    find_library(SFML_WINDOW sfml-window libs/sfml-macos/lib)
    find_library(SFML_GRAPHICS sfml-graphics libs/sfml-macos/lib)
    find_library(SFML_NETWORK sfml-network libs/sfml-macos/lib)
    find_library(SFML_AUDIO sfml-audio libs/sfml-macos/lib)
    target_link_libraries(Sokoban sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
endif(APPLE)

target_link_libraries(Sokoban ${Boost_LIBRARIES})
