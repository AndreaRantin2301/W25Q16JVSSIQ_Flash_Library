cmake_minimum_required(VERSION 3.23...4.3)

project(W25Q16JVSSIQ
    VERSION 1.0.0
    DESCRIPTION "A portable, pure C library to control the W25Q16JVSSIQ flash chip"
    LANGUAGES C ASM
    HOMEPAGE_URL "https://github.com/AndreaRantin2301/W25Q16JVSSIQ_Flash_Library" 
)

option(W25Q16JVSSIQ_BUILD_EXAMPLES "Build the example projects" ON)

add_subdirectory(lib)

if(W25Q16JVSSIQ_BUILD_EXAMPLES)
    add_subdirectory(examples/stm32)
endif()