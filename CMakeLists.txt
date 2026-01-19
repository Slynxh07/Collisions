cmake_minimum_required(VERSION 3.10)

project(Collisions)

set(C_STANDARD 17)
set(C_STANDARD_REQUIRED ON)
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

find_package(SDL2 REQUIRED)

file(GLOB SRC_FILES "${SRC_DIR}/*.c")
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main m)