cmake_minimum_required(VERSION 3.10)
project(TrueManager)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


file(GLOB SOURCES "src/*.cpp")


add_executable(TrueManager ${SOURCES})


target_link_libraries(TrueManager ${CURSES_LIBRARIES})
