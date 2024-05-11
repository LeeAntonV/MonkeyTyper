cmake_minimum_required(VERSION 3.27)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)
add_executable(main main.cpp
        StartMenu/StartMenu.cpp
        StartMenu/StartMenu.h
        StartMenu/Button.h
        Typer/MonkeyTyper.cpp
        Typer/MonkeyTyper.h)
target_link_libraries(main sfml-graphics)

