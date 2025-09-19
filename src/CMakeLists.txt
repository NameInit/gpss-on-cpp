cmake_minimum_required(VERSION 3.10)
project(gpss)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.cpp" "data_io/*.cpp" "main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(run
    DEPENDS ${PROJECT_NAME}
    COMMAND ./${PROJECT_NAME}
)

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/report
    COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_NAME}
)