file(GLOB_RECURSE CLIENT_LIB_SOURCES "*.cpp")
list(REMOVE_ITEM CLIENT_LIB_SOURCES "main.cpp")

add_library(client-lib STATIC ${CLIENT_LIB_SOURCES})
target_link_libraries(client-lib
        PUBLIC common-lib)
target_include_directories(client-lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(client main.cpp)
target_link_libraries(client
        PUBLIC client-lib)
