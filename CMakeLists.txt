cmake_minimum_required(VERSION 3.16)

project(SpaceSalvager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/SpaceSalvager")

set(SOURCES
    src/SpaceSalvager.cpp
    src/Engine.cpp
    src/InputEngine.cpp
    src/UpdateEngine.cpp
    src/DrawEngine.cpp
    src/World.cpp
    src/InputManager.cpp
    src/Asteroid.cpp
    src/CollisionManager.cpp
    src/GameplayManager.cpp
    src/HUD.cpp
    src/SalvageObject.cpp
    src/ResourceManager.cpp
    src/Ship.cpp
)

set(HEADERS
    src/Engine.h
    src/World.h
    src/BaseGameObject.h
    src/InputManager.h
    src/Asteroid.h
    src/CollisionManager.h
    src/GameplayManager.h
    src/HUD.h
    src/SalvageObject.h
    src/ResourceManager.h
    src/Ship.h
    src/MathFunction.h
    src/RandomNumber.h
    src/WorldBound.h
)

add_executable(
    SpaceSalvager
    ${SOURCES}
    ${HEADERS}
)

if(WIN32)
    set(SFML_STATIC_LIBRARIES ON)
endif()

find_package(
    SFML 2.5 REQUIRED
    COMPONENTS graphics window system
)

target_link_libraries(
    SpaceSalvager
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

add_custom_command(
    TARGET SpaceSalvager
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:SpaceSalvager>/res"
)
