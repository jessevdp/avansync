file(GLOB_RECURSE COMMON_LIB_SOURCES "*.cpp")
add_library(common-lib STATIC ${COMMON_LIB_SOURCES})

find_package(Threads REQUIRED)

set(ASIO_DIR ${CMAKE_SOURCE_DIR}/vendor/asio-1.18.0)
find_package(Asio REQUIRED)
add_compile_definitions(ASIO_STANDALONE=YES)

target_include_directories(common-lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${ASIO_INCLUDE_DIRS}
        PUBLIC std::filesystem)

target_link_libraries(common-lib
        PRIVATE ${CMAKE_THREAD_LIBS_INIT})
