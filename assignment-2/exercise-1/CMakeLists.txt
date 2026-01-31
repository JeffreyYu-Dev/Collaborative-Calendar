cmake_minimum_required(VERSION 3.10)
project(exercise-one)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 REQUIRED)

add_executable(exercise-one exercise-one.cpp)

target_link_libraries(exercise-one 
    glfw
    "-framework OpenGL"
)


configure_file(dog.txt dog.txt COPYONLY)