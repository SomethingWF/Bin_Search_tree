# ��������� ����������� ������ CMake
cmake_minimum_required(VERSION 3.10)

# ��������� ��� ������� � ������
project(MyProject)

# ��������� �������� C++
set(CMAKE_CXX_STANDARD 17)

add_executable(Heap_tree Heap_tree.cpp)
add_executable(AVL_tree AVL_tree.cpp)