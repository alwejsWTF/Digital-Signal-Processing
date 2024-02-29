cmake_minimum_required(VERSION 3.23)

project(Library)

set(SOURCE_FILES
        src/Signal.cpp include/Signal.h
        src/SinusoidalSignal.cpp include/SinusoidalSignal.h src/RectangularSignal.cpp include/RectangularSignal.h src/TriangularSignal.cpp include/TriangularSignal.h)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_link_libraries(Library)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)