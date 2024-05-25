cmake_minimum_required(VERSION 3.23)
project(Library)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.10.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SOURCE_FILES
        src/ContinuousSignal.cpp
        src/DiscreteSignal.cpp
        src/signals/GaussianNoise.cpp
        src/signals/ImpulseNoise.cpp
        src/signals/RectangularSignal.cpp
        src/signals/RectangularSymmetricSignal.cpp
        src/signals/SinusoidalFullRectifiedSignal.cpp
        src/signals/SinusoidalHalfRectifiedSignal.cpp
        src/signals/SinusoidalSignal.cpp
        src/signals/TriangularSignal.cpp
        src/signals/UniformDistributionNoise.cpp
        src/signals/UnitImpulseSignal.cpp
        src/signals/UnitStepSignal.cpp
        src/utils/FileOperations.cpp
        src/utils/SignalOperations.cpp
        src/Signal.cpp
        src/signals/Quantizer.cpp
        src/signals/SignalReconstruction.cpp
        src/utils/Measures.cpp
        src/utils/convolution.cpp
        include/utils/convolution.h
        src/utils/filters.cpp
        include/utils/filters.h
        src/utils/crossCorrelation.cpp
        include/utils/crossCorrelation.h
        src/utils/sensor.cpp
        include/utils/sensor.h
)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_link_libraries(Library nlohmann_json::nlohmann_json)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)