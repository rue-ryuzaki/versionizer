project("versionizer")
cmake_minimum_required(VERSION 3.2)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wold-style-cast -Wextra -Wundef -Wsign-compare -Wconversion -Wpointer-arith -Weffc++ -Wnon-virtual-dtor")
endif()

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(src)
include_directories(third_party)

file(GLOB_RECURSE PROJECT_HEADERS "include/*.h*")
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

set(SRC_LIST ${PROJECT_HEADERS} ${PROJECT_SOURCES})

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

enable_testing()
add_subdirectory(test)
