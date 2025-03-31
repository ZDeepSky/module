cmake_minimum_required(VERSION 3.15)

project(service)

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

file(GLOB_RECURSE client_source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

message(${CMAKE_CURRENT_BINARY_DIR})


add_executable(${PROJECT_NAME} ${client_source})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)           

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ROOT_PATH}/bin"
)