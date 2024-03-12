cmake_minimum_required(VERSION 3.23)

project(Program)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

set(SOURCE_FILES src/main.cpp)
add_executable(Program ${SOURCE_FILES})

add_definitions(-DWITHOUT_NUMPY)


include_directories(${Python3_INCLUDE_DIRS} include)

target_link_libraries(Program PUBLIC Library ${Python3_LIBRARIES})
target_include_directories(Program PUBLIC include)
