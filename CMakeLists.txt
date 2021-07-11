cmake_minimum_required(VERSION 3.19)
project(kphoh)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/CSVParser)
include_directories(include/hash)
include_directories(include/hashmap)
include_directories(include/hcrstrat)
include_directories(include/umash)

add_executable(kphoh
        data/ct.csv
        data/it.csv
        data/mc.csv
        include/CSVParser/CSVParser.cpp
        include/CSVParser/CSVParser.h
        include/hash/loadHash.h
        include/hash/sph.h
        include/hash/t1ha.h
        include/hash/wyhash.h
        include/hash/xxh.h
        include/hash/xxhash.c
        include/hash/xxhash.h
        include/hashmap/hashmap_scalar.h
        include/hcrstrat/linear_probing.h
        include/umash/umash.h
        main.cpp include/hash/mum.h)
