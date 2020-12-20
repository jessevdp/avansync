file(GLOB_RECURSE SERVER_LIB_SOURCES "*.cpp")
list(REMOVE_ITEM SERVER_LIB_SOURCES "main.cpp")

add_library(server-lib STATIC ${SERVER_LIB_SOURCES})

target_include_directories(server-lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Asio REQUIRED)
include_directories(${ASIO_INCLUDE_DIR})

add_executable(server main.cpp)
target_link_libraries(server
        PUBLIC server-lib)