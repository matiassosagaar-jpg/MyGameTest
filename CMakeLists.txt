cmake_minimum_required(VERSION 3.16)
project(MyGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/WaveSpawner.cpp
)

add_subdirectory(external/raylib)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    include
)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11)
endif()