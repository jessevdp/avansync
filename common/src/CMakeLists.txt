file(GLOB_RECURSE COMMON_LIB_SOURCES "*.cpp")
add_library(common-lib STATIC ${COMMON_LIB_SOURCES})

find_package(Threads REQUIRED)

find_package(Filesystem REQUIRED COMPONENTS Final Experimental)
if (CXX_FILESYSTEM_IS_EXPERIMENTAL)
    add_compile_definitions(CXX_FILESYSTEM_IS_EXPERIMENTAL)
endif ()

set(ASIO_DIR ${CMAKE_SOURCE_DIR}/vendor/asio-1.18.0)
find_package(Asio REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES")

target_include_directories(common-lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${ASIO_INCLUDE_DIRS}
        PRIVATE std::filesystem)

target_link_libraries(common-lib
        PRIVATE ${CMAKE_THREAD_LIBS_INIT})
