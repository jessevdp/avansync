cmake_minimum_required(VERSION 3.17)
project(AvanSync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/asio-1.18.0/include)
include_directories(${ASIO_INCLUDE_DIR}) # TODO: 'protect' this more?
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES" -pthread)

add_subdirectory(client)
add_subdirectory(server)

