file(GLOB_RECURSE SERVER_LIB_SOURCES "*.cpp")
list(REMOVE_ITEM SERVER_LIB_SOURCES "main.cpp")

add_library(server-lib STATIC ${SERVER_LIB_SOURCES})
target_include_directories(server-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# TODO: move threads and Asio dependencies to server-lib?
find_package(Threads REQUIRED)
find_package(Asio REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES")
include_directories(${ASIO_INCLUDE_DIRS})

add_executable(server main.cpp)
target_link_libraries(server
        PUBLIC server-lib
        PRIVATE ${CMAKE_THREAD_LIBS_INIT})