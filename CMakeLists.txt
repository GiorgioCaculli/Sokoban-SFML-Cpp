cmake_minimum_required(VERSION 3.20)
project(SokobanSFML VERSION 1.2.0 DESCRIPTION "GzC Sokoban Game")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-march=native -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-mtune=generic -O2 -Wpedantic")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef")
set(THREADS_PREFER_PTHREAD_FLAG ON)

include(GNUInstallDirs)
include(CPack)
include(FindPkgConfig)
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VENDOR "Giorgio Caculli")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
if (WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full UNIX paths properly.
    # Make sure there is at least one set of four backlashes.
    set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\SokobanSDL.exe")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} SokobanSDL")
    set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.gitlab.com\\\\GiorgioCaculli\\\\Sokoban-SDL-CPP")
    set(CPACK_NSIS_URL_INFO_ABOUT "https:\\\\\\\\www.gitlab.com\\\\GiorgioCaculli\\\\Sokoban-SDL-Cpp")
    set(CPACK_NSIS_CONTACT "giorgio.caculli@icloud.com")
    set(CPACK_NSIS_MODIFY_PATH ON)
else ()
    set(CPACK_STRIP_FILES "bin/SokobanSDL")
    set(CPACK_SOURCE_STRIP_FILES "")
endif ()
set(CPACK_PACKAGE_EXECUTABLES "SokobanSDL" "${CMAKE_PROJECT_DESCRIPTION}")

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_library(GZC_UTIL gzc_util REQUIRED)
find_library(GZC_GAMES_SOKOBAN gzc_sokoban REQUIRED)

set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 3 REQUIRED COMPONENTS Audio Graphics Network System Window)
find_package(Boost REQUIRED CONFIG COMPONENTS filesystem)

include_directories(${SFML_INCLUDE_DIRS} ${GZC_GAMES_SOKOBAN_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
include_directories(include)

add_executable(SokobanSFML
        src/main.cpp
        src/ui/Menu.cpp
        src/gui/Animation.cpp
        src/gui/Application.cpp
        src/gui/Music_Player.cpp
        src/gui/Scene_Node.cpp
        src/gui/Sound_Node.cpp
        src/gui/Sound_Player.cpp
        src/gui/Sprite_Node.cpp
        src/gui/Utility.cpp
        src/gui/World.cpp
        src/gui/Resource_Bundle.cpp
        src/gui/states/State.cpp
        src/gui/states/State_Game.cpp
        src/gui/states/State_Menu.cpp
        src/gui/states/State_Pause.cpp
        src/gui/states/State_Settings.cpp
        src/gui/states/State_Stack.cpp
        src/gui/states/State_Title.cpp
        src/gui/entities/Entity.cpp
        src/gui/entities/Entity_Box.cpp
        src/gui/entities/Entity_Movable.cpp
        src/gui/entities/Entity_Platform.cpp
        src/gui/entities/Entity_Player.cpp
        src/gui/entities/Entity_Wall.cpp
        src/gui/components/Component.cpp
        src/gui/components/Button.cpp
        src/gui/components/Container.cpp
        src/gui/components/Label.cpp
        src/net/Packet.cpp
        src/net/Client.cpp
        src/net/Server.cpp
        src/input/Keyboard.cpp
        src/input/Mouse.cpp
        src/input/Gamepad.cpp)

target_link_libraries(SokobanSFML PUBLIC ${GZC_GAMES_SOKOBAN} ${GZC_UTIL} SFML::Audio SFML::Graphics SFML::Network SFML::System SFML::Window ${Boost_LIBRARIES})
