cmake_minimum_required(VERSION 3.19)
project(Sokoban VERSION 1.1.0 DESCRIPTION "GzC Sokoban Game")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS OFF)

include_directories(include)

add_executable(Sokoban
        src/main.cpp
        src/ui/Menu.cpp
        src/ui/gui/Animation.cpp
        src/ui/gui/Application.cpp
        src/ui/gui/Music_Player.cpp
        src/ui/gui/Scene_Node.cpp
        src/ui/gui/Sound_Node.cpp
        src/ui/gui/Sound_Player.cpp
        src/ui/gui/Sprite_Node.cpp
        src/ui/gui/Utility.cpp
        src/ui/gui/World.cpp
        src/ui/gui/states/State.cpp
        src/ui/gui/states/State_Game.cpp
        src/ui/gui/states/State_Menu.cpp
        src/ui/gui/states/State_Pause.cpp
        src/ui/gui/states/State_Settings.cpp
        src/ui/gui/states/State_Stack.cpp
        src/ui/gui/states/State_Title.cpp
        src/ui/gui/entities/Entity.cpp
        src/ui/gui/entities/Entity_Box.cpp
        src/ui/gui/entities/Entity_Movable.cpp
        src/ui/gui/entities/Entity_Platform.cpp
        src/ui/gui/entities/Entity_Player.cpp
        src/ui/gui/entities/Entity_Wall.cpp
        src/ui/gui/components/Component.cpp
        src/ui/gui/components/Button.cpp
        src/ui/gui/components/Container.cpp
        src/ui/gui/components/Label.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    # Global libraries
    find_package(Boost COMPONENTS date_time locale log filesystem unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})
    find_library(GzC_Util_Logger_LIBRARY util_logger)
    find_library(GzC_Util_Serialize_LIBRARY util_serialize)
    find_library(Gzc_Sokoban_Core_LIBRARY sokoban_core)
    include_directories(include/sfml-windows)
    link_directories(${CMAKE_SOURCE_DIR}/libs/sfml-windows/lib)
    find_library(SFML_System_LIBRARY NAMES sfml-system HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-windows/lib)
    find_library(SFML_Window_LIBRARY NAMES sfml-window HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-windows/lib)
    find_library(SFML_Graphics_LIBRARY NAMES sfml-graphics HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-windows/lib)
    find_library(SFML_Network_LIBRARY NAMES sfml-network HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-windows/lib)
    find_library(SFML_Audio_LIBRARY NAMES sfml-audio HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-windows/lib)
    target_link_libraries(Sokoban PUBLIC
            ${SFML_Audio_LIBRARY} ${SFML_Network_LIBRARY} ${SFML_Graphics_LIBRARY} ${SFML_Window_LIBRARY} ${SFML_System_LIBRARY}
            ${Gzc_Sokoban_Core_LIBRARY} ${GzC_Util_Logger_LIBRARY} ${GzC_Util_Serialize_LIBRARY} ${Boost_LIBRARIES})
endif(WIN32)

if(UNIX AND NOT APPLE)
    # Global libraries
    find_package(Boost COMPONENTS date_time locale log filesystem unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})
    find_library(GzC_Util_Logger_LIBRARY util_logger)
    find_library(GzC_Util_Serialize_LIBRARY util_serialize)
    find_library(Gzc_Sokoban_Core_LIBRARY sokoban_core)
    include_directories(include/sfml-unix)
    link_directories(${CMAKE_SOURCE_DIR}/libs/sfml-unix/lib)
    find_library(SFML_System_LIBRARY NAMES sfml-system HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-unix/lib)
    find_library(SFML_Window_LIBRARY NAMES sfml-window HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-unix/lib)
    find_library(SFML_Graphics_LIBRARY NAMES sfml-graphics HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-unix/lib)
    find_library(SFML_Network_LIBRARY NAMES sfml-network HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-unix/lib)
    find_library(SFML_Audio_LIBRARY NAMES sfml-audio HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-unix/lib)
    target_link_libraries(Sokoban PUBLIC
            ${SFML_Audio_LIBRARY} ${SFML_Network_LIBRARY} ${SFML_Graphics_LIBRARY} ${SFML_Window_LIBRARY} ${SFML_System_LIBRARY}
            ${Gzc_Sokoban_Core_LIBRARY} ${GzC_Util_Logger_LIBRARY} ${GzC_Util_Serialize_LIBRARY} ${Boost_LIBRARIES})
endif(UNIX AND NOT APPLE)

if(APPLE)
    # Global libraries
    find_package(Boost COMPONENTS date_time locale log filesystem unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})
    find_library(GzC_Util_Logger_LIBRARY util_logger)
    find_library(GzC_Util_Serialize_LIBRARY util_serialize)
    find_library(Gzc_Sokoban_Core_LIBRARY sokoban_core)
    include_directories(include/sfml-macos)
    link_directories(${CMAKE_SOURCE_DIR}/libs/sfml-macos/lib)
    find_library(SFML_System_LIBRARY NAMES sfml-system HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-macos/lib)
    find_library(SFML_Window_LIBRARY NAMES sfml-window HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-macos/lib)
    find_library(SFML_Graphics_LIBRARY NAMES sfml-graphics HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-macos/lib)
    find_library(SFML_Network_LIBRARY NAMES sfml-network HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-macos/lib)
    find_library(SFML_Audio_LIBRARY NAMES sfml-audio HINTS ${CMAKE_SOURCE_DIR}/libs/sfml-macos/lib)
    target_link_libraries(Sokoban PUBLIC
            ${SFML_Audio_LIBRARY} ${SFML_Network_LIBRARY} ${SFML_Graphics_LIBRARY} ${SFML_Window_LIBRARY} ${SFML_System_LIBRARY}
            ${Gzc_Sokoban_Core_LIBRARY} ${GzC_Util_Logger_LIBRARY} ${GzC_Util_Serialize_LIBRARY} ${Boost_LIBRARIES})
endif(APPLE)
