cmake_minimum_required(VERSION 3.22)

project(W25Q16JVSSIQ)

enable_language(C)

set(LIBRARY_NAME W25Q16JVSSIQ)

add_library(${LIBRARY_NAME} STATIC
    src/w25q16jv.c
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(${LIRARY_NAME} PUBLIC c_std_17)