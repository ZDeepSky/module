cmake_minimum_required(VERSION 3.15)
project(epoll_service)

include(depends.cmake)

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

file(GLOB_RECURSE source_file
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

message(${PUB_INCLUDE})


add_executable(${PROJECT_NAME} ${source_file})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRI_INCLUDE})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUB_INCLUDE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)           

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ROOT_PATH}/bin"
)