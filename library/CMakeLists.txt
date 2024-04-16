cmake_minimum_required(VERSION 3.23)

project(Library)

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
        src/utils/Sampler.cpp
        include/utils/Sampler.h
        src/utils/Quantizer.cpp
        include/utils/Quantizer.h
        src/utils/SignalReconstruction.cpp
        include/utils/SignalReconstruction.h
        src/utils/Measures.cpp
        include/utils/Measures.h)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_link_libraries(Library)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)