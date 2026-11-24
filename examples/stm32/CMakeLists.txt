cmake_minimum_required(VERSION 3.22)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Selected build type for stm32 example: ${CMAKE_BUILD_TYPE}")

set(EXAMPLE_NAME "W25QJVSSIQ_STM32_Example")

project(${EXAMPLE_NAME}
    VERSION 1.0.0
    DESCRIPTION "Example project built for STM32F303RE"
    LANGUAGES C ASM
)

add_executable(${EXAMPLE_NAME})

set_target_properties(${EXAMPLE_NAME}
    PROPERTIES SUFFIX ".elf"
)

add_subdirectory(cmake/stm32cubemx)

if(NOT TARGET AndreaRantin::W25Q16JVSSIQ_Library)
     add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
        ${CMAKE_CURRENT_BINARY_DIR}/w25q16jvssiq
    )
endif()

target_link_libraries(${EXAMPLE_NAME}
    stm32cubemx
    AndreaRantin::W25Q16JVSSIQ_Library
)