cmake_minimum_required(VERSION 3.10)
project(exercise-two)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 REQUIRED)

add_executable(exercise-two exercise-two.cpp)

target_link_libraries(exercise-two 
    glfw
    "-framework OpenGL"
)

