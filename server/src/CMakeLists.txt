file(GLOB_RECURSE SERVER_LIB_SOURCES "*.cpp")
list(REMOVE_ITEM SERVER_LIB_SOURCES "main.cpp")

add_library(server-lib STATIC ${SERVER_LIB_SOURCES})
target_link_libraries(server-lib
        PUBLIC common-lib)
target_include_directories(server-lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(server main.cpp)
target_link_libraries(server
        PUBLIC server-lib)