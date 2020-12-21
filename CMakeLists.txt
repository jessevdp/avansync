cmake_minimum_required(VERSION 3.17)
project(AvanSync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(ASIO_DIR ${CMAKE_SOURCE_DIR}/vendor/asio-1.18.0)

add_subdirectory(client)
add_subdirectory(server)

