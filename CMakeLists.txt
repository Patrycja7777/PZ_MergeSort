cmake_minimum_required(VERSION 3.14)
project(PZ_MergeSort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

add_executable(PZ_MergeSort main.cpp)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
            URL_HASH SHA256=edd885a1ab32b6999515a880f669efadb80b3f880215f315985fa3f6eca7c4d3
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(MergeSortTests tests/MergeSortTests.cpp)

    target_include_directories(
            MergeSortTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    target_link_libraries(MergeSortTests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(MergeSortTests)
endif()