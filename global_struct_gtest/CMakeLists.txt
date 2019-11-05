# Get the exercise name from the current directory
get_filename_component(exercise ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Basic CMake project
cmake_minimum_required(VERSION 3.15)

# Name the project after the exercise
project(${exercise} C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# we will use the network to fetch Google Test sources
# make it possible to disable unit tests when not on network
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if (ENABLE_UNIT_TESTS)
    enable_testing()
    # the following code to fetch googletest
    # is inspired by and adapted after:
    #   - https://cmake.org/cmake/help/v3.11/module/FetchContent.html
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.10.0
    )

    FetchContent_GetProperties(googletest)

    if (NOT googletest_POPULATED)
        FetchContent_Populate(googletest)

        # Prevent GoogleTest from overriding our compiler/linker options
        # when building with Visual Studio
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        # Prevent GoogleTest from using PThreads
        set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

        # adds the targets: gtest, gtest_main, gmock, gmock_main
        add_subdirectory(
                ${googletest_SOURCE_DIR}
                ${googletest_BINARY_DIR}
        )

        # Silence std::tr1 warning on MSVC
        if (MSVC)
            foreach (_tgt gtest gtest_main gmock gmock_main)
                target_compile_definitions(${_tgt}
                        PRIVATE
                        "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
                        )
            endforeach ()
        endif ()
    endif ()

    include(GoogleTest)

    # Disable pthread support because mocked calls fail with segfault
    # this is a known bug with cmake on ubuntu and we don't need the functionality.
    add_definitions("-DGTEST_HAS_PTHREAD=0")

    add_executable(global_struct_test "")
    target_sources(global_struct_test
            PRIVATE
            global_struct_test.cpp
            global_struct.cpp
            global_struct.h
            )
    target_link_libraries(global_struct_test
            PRIVATE
            gmock_main gtest gmock
            )
    gtest_discover_tests(global_struct_test)
endif ()
