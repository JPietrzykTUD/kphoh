cmake_minimum_required(VERSION 3.19)
project(hoh)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(hoh main.cpp include/hash/xxh.h include/hash/loadHash.h include/hash/wyhash.h include/hash/xxhash.h
        include/hash/xxhash.c)

