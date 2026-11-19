cmake_minimum_required(VERSION 3.22)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_PROJECT_NAME W25Q16JVSSIQ_Example)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
enable_language(C ASM)


add_executable(${PROJECT_NAME})

add_subdirectory(cmake/stm32cubemx)

target_link_libraries(${PROJECT_NAME}
    stm32cubemx
)
