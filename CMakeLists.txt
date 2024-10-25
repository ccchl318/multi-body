cmake_minimum_required(VERSION 3.10)
project(multi_body)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(multi_body main.cpp particle.h system.h system.cpp
        rendering.cpp
        rendering.h
        gui.cpp
        gui.h
)
target_include_directories(multi_body PRIVATE ${EIGEN3_INCLUDE_DIRS})
target_link_libraries(multi_body PRIVATE ${OpenCV_LIBRARIES})
