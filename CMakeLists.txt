cmake_minimum_required(VERSION 3.28)
project(2048 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable parallel builds
set(CMAKE_BUILD_PARALLEL_LEVEL 0 CACHE STRING "Number of parallel build jobs")

# Use ccache if available for faster rebuilds
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_CXX_MODULE_CMI "${CCACHE_PROGRAM}")
endif()

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(SFML_STATIC_LIBRARIES ON CACHE BOOL "Link SFML statically" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

# Try to find SFML package first (much faster if installed)
find_package(SFML 3.0 COMPONENTS Graphics Audio CONFIG QUIET)

if(NOT SFML_FOUND)
    # Fall back to FetchContent only if SFML is not found
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

set(SOURCES
    src/main.cpp
    src/game2048.cpp
    src/game/board.cpp
    src/game/random.cpp
    src/game/scoreStorage.cpp
    src/game/stringToInt.cpp
    src/input/keyboard.cpp
    src/input/mouse.cpp
    src/ui/assets.cpp
    src/ui/boardRenderer.cpp
    src/ui/button.cpp
    src/ui/element.cpp
    src/ui/windowManager.cpp
    src/ui/screens/base.cpp
    src/ui/screens/game.cpp
    src/ui/screens/menu.cpp
)

if(WIN32)
# Add WIN32 before ${SOURCES} to remove the debug console.
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} resources/icon.rc)
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio SFML::Main)
elseif(APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE 2048.icns)
    target_sources(${PROJECT_NAME} PRIVATE resources/2048.icns)
    set_source_files_properties(resources/2048.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio)
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/assets)
