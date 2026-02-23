cmake_minimum_required(VERSION 3.20)
project(musicpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(musicpp ${SOURCES})

target_include_directories(musicpp PRIVATE
    src/
    include/
    third_party/
)

if(WIN32)
    target_link_libraries(musicpp PRIVATE ole32 user32)
endif()

if(MSVC)
    target_compile_options(musicpp PRIVATE /W4)
else()
    target_compile_options(musicpp PRIVATE -Wall -Wextra -Wpedantic)
endif()
