cmake_minimum_required(VERSION 3.28)
project(directed_percolation_test)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
add_executable(directed_percolation_test main.cpp)

target_link_libraries(directed_percolation_test ${SDL2_LIBRARIES})
