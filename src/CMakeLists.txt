cmake_minimum_required(VERSION 3.10)
project(gpss)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "source/*.cpp" "data_io/*.cpp" "main.cpp")
file(GLOB HEADERS "source/*.h" "data_io/*.h" "headers/*.h")

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

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(clang
        COMMAND ${CLANG_FORMAT} -i --style=file ${SOURCES} ${HEADERS}
        COMMENT "Форматирование кода с помощью clang-format"
    )
else()
    message(WARNING "clang-format не найден. Цель 'clang' недоступна.")
endif()