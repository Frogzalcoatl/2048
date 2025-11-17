cmake_minimum_required(VERSION 3.28)
project(2048 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
src/main.cpp
src/game2048.cpp
src/game/board.cpp
src/game/random.cpp
src/input/keyboard.cpp
src/input/mouse.cpp
src/ui/assets.cpp
src/ui/boardRenderer.cpp
src/ui/button.cpp
src/ui/element.cpp
src/ui/screens/base.cpp
src/ui/screens/game.cpp
src/ui/screens/menu.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
file(COPY ${CMAKE_SOURCE_DIR}/assets 
     DESTINATION ${CMAKE_BINARY_DIR}/assets)
