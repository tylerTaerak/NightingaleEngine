cmake_minimum_required(VERSION 3.7)

project(NightingaleEngine VERSION 0.1.0 DESCRIPTION "A modular engine for writing games")

include(FetchContent)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
# set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
    message(STATUS "Found SDL: ${SDL2_PREFIX}")
endif()

find_package(SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)

find_package(OpenAL REQUIRED)

find_package(ALUT REQUIRED)

find_package(Freetype REQUIRED)

find_package(glm REQUIRED)

file(GLOB_RECURSE
    HEADER_FILES
    include/*.hpp)

file(GLOB_RECURSE
    SOURCE_FILES
    src/*.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${OPENAL_INCLUDE_DIRS}
        ${ALUT_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${ALUT_LIBRARIES}
        glm::glm
        ${SDL2_IMAGE_LIBRARIES}
        ${FREETYPE_LIBRARIES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        include
        include/audio
        include/content
        include/ecs
        include/game_states
        include/graphics
        include/graphics/2d
        include/graphics/particles
        include/sdl
        include/state_machines
        include/utils
    INTERFACE
        ${FREETYPE_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${OPENAL_INCLUDE_DIRS}
        ${ALUT_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(FILES ${HEADER_FILES} DESTINATION include/NightingaleEngine)

message(STATUS "Retrieving GTest for testing")

file(GLOB_RECURSE
    TEST_FILES
    test/*.cpp)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    NightingaleTests
    ${TEST_FILES}
    test/test_main.cpp
)

target_link_libraries(
    NightingaleTests
    ${PROJECT_NAME} 
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(NightingaleTests)
