file(GLOB_RECURSE CLIENT_LIB_SOURCES "*.cpp")
list(REMOVE_ITEM CLIENT_LIB_SOURCES "main.cpp")

add_library(client-lib STATIC ${CLIENT_LIB_SOURCES})
target_include_directories(client-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# TODO: move these dependencies to client-lib?
find_package(Threads REQUIRED)
find_package(Asio REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES")
include_directories(${ASIO_INCLUDE_DIRS})

add_executable(client main.cpp)
target_link_libraries(client
        PUBLIC client-lib
        PRIVATE ${CMAKE_THREAD_LIBS_INIT})
