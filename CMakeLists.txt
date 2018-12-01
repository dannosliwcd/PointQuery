cmake_minimum_required(VERSION 3.6)

project(PointQuery)

set (CMAKE_CXX_STANDARD 11)

include(CheckCXXCompilerFlag)
include(CMakePushCheckState)

# Dynamic analysis. If available, use ASAN and UBSAN on debug builds.
option(ENABLE_SANITIZERS "Enable sanitizers" ON)
if(ENABLE_SANITIZERS)
    cmake_push_check_state(RESET)
    SET(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
    check_cxx_compiler_flag("-fsanitize=address" ASAN_SUPPORTED)
    cmake_pop_check_state()

    cmake_push_check_state(RESET)
    SET(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    check_cxx_compiler_flag("-fsanitize=undefined" UBSAN_SUPPORTED)
    cmake_pop_check_state()

    if(ASAN_SUPPORTED OR UBSAN_SUPPORTED)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer")
        set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer")

        if(ASAN_SUPPORTED)
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
            set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fsanitize=address")
        endif()
        if(UBSAN_SUPPORTED)
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")
            set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fsanitize=undefined")
        endif()
    endif()
endif()

add_subdirectory(thirdparty/cli11)
add_subdirectory(thirdparty/catch)
add_subdirectory(src)

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/thirdparty/catch")
include(CTest)
include(Catch)
enable_testing()
add_subdirectory(test)
