cmake_minimum_required(VERSION 3.17)
project(AvanSync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# TODO: move this to common-lib?
find_package(Filesystem REQUIRED COMPONENTS Final Experimental)
if (CXX_FILESYSTEM_IS_EXPERIMENTAL)
    add_compile_definitions(CXX_FILESYSTEM_IS_EXPERIMENTAL)
endif()

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
