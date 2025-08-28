# Sokoban Game written in C++20 and SFML 3

![GAME](doc/finalsprint/pictures/jeu.png "jeu.png")

## Authors:
- Giorgio Caculli <[giorgio.caculli@icloud.com](mailto:giorgio.caculli@icloud.com)>
- Guillaume Lambert
- Tanguy Taminiau
- Nathan Thaon

## Dependencies
- [SFML 3.0.1](https://www.sfml-dev.org/)
- [GzC Sokoban Core](https://www.gitlab.com/GiorgioCaculli/Sokoban-Cpp)
- [GzC Utils](https://www.gitlab.com/GiorgioCaculli/Util-Cpp)

## Build Tools:
- [CMake](https://cmake.org/)

## Building Instructions:

- Use `git clone --recursive` to clone this repo

### CMake

#### SFML
1. `cd SFML`
2. `mkdir build`
3. `cd build`
4. `cmake -DBUILD_SHARED_LIBS=on ..`
5. `make`
6. `./Sokoban`

#### Sokoban
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`
5. `./Sokoban`
