file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(server-tests ${TEST_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/vendor/fakeit/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

Include(FetchContent)
FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.2.2)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(server-tests
        PUBLIC server-lib
        Catch2::Catch)

include(CTest)
include(Catch)
catch_discover_tests(server-tests)