cmake_minimum_required(VERSION 3.1)
project(LifeSimulator)

#Put executebles and binnarys in bin folder
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "include/*.h") #Selects all c++ files
set(CMAKE_CXX_STANDARD 11) #Use C++11
add_executable(LifeSimulator ${SOURCES})
