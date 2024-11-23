# ”казываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# ”казываем им€ проекта и версию
project(MyProject)

# ”казываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

add_executable(Heap_tree Heap_tree.cpp)
add_executable(AVL_tree AVL_tree.cpp)