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

#########################################################################
# Catch unit testing
#########################################################################

set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/Catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(unitTests ${TEST_SOURCES})
target_link_libraries(unitTests Catch)

enable_testing()
add_test(NAME MainUnitTests COMMAND unitTests)
