cmake_minimum_required(VERSION 3.23)

set(LIBRARY_NAME W25Q16JVSSIQ_Library)

project(${LIBRARY_NAME}
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(${LIBRARY_NAME} STATIC)
add_library(AndreaRantin::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_sources(${LIBRARY_NAME}
    PRIVATE
        src/w25q16jvssiq.c
    PRIVATE
        FILE_SET libPrivateHeaders
        TYPE HEADERS
        BASE_DIRS
            src
        FILES
            src/w25q16jvssiq_private.h
    PUBLIC
        FILE_SET libHeaders
        TYPE HEADERS
        BASE_DIRS 
            inc
        FILES
            inc/w25q16jvssiq/w25q16jvssiq.h

)

if(MSVC)
    target_compile_options(${LIBRARY_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${LIBRARY_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wdouble-promotion
        -Wundef
        -Wswitch-enum
        -Wstrict-prototypes
        -Wmissing-prototypes
        -Wold-style-definition
        -Wredundant-decls
        -Wcast-align
        -Wcast-qual
        -Wformat=2
        -Wformat-signedness
        -Wimplicit-fallthrough=5
        -Wnull-dereference
    )
endif()