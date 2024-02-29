cmake_minimum_required(VERSION 3.23)

project(Program)

set(SOURCE_FILES src/main.cpp)

add_executable(Program ${SOURCE_FILES})
target_link_libraries(Program PUBLIC Library)
target_include_directories(Program PUBLIC include)
