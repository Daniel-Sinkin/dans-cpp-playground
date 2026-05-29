cmake_minimum_required(VERSION 3.20)

if(APPLE AND NOT DEFINED CMAKE_C_COMPILER AND NOT DEFINED CMAKE_CXX_COMPILER)
    foreach(DANS_CPP_PLAYGROUND_LLVM_PREFIX IN ITEMS /opt/homebrew/opt/llvm /usr/local/opt/llvm)
        if(EXISTS "${DANS_CPP_PLAYGROUND_LLVM_PREFIX}/bin/clang" AND EXISTS "${DANS_CPP_PLAYGROUND_LLVM_PREFIX}/bin/clang++")
            set(CMAKE_C_COMPILER "${DANS_CPP_PLAYGROUND_LLVM_PREFIX}/bin/clang" CACHE FILEPATH "C compiler" FORCE)
            set(CMAKE_CXX_COMPILER "${DANS_CPP_PLAYGROUND_LLVM_PREFIX}/bin/clang++" CACHE FILEPATH "C++ compiler" FORCE)
            message(STATUS "Using LLVM toolchain from ${DANS_CPP_PLAYGROUND_LLVM_PREFIX}")
            break()
        endif()
    endforeach()
endif()

project(dans_cpp_playground LANGUAGES C CXX)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# dans-core: header-only, vendored as plain files under vendor/dans-core.
add_library(dans_core INTERFACE)
add_library(dans::core ALIAS dans_core)
target_compile_features(dans_core INTERFACE cxx_std_23)
target_include_directories(dans_core SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dans-core/include
)

# dans-util: vendored as plain files under vendor/dans-util, built against the
# vendored dans-core above (its own bundled dans-core was dropped).
add_library(dans_util STATIC
    vendor/dans-util/src/chrono.cpp
    vendor/dans-util/src/dev.cpp
    vendor/dans-util/src/env.cpp
    vendor/dans-util/src/fmt.cpp
    vendor/dans-util/src/random.cpp
    vendor/dans-util/src/str.cpp
    vendor/dans-util/src/util.cpp
)
add_library(dans::util ALIAS dans_util)
target_link_libraries(dans_util PUBLIC dans::core)
target_include_directories(dans_util SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dans-util/include
)
target_precompile_headers(dans_util PRIVATE
    <dans/pch.hpp>
)

add_library(dans_cpp_playground_warnings INTERFACE)
target_compile_options(dans_cpp_playground_warnings INTERFACE
    $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wshadow
        -Wconversion
        -Wfloat-conversion
        -Wsign-conversion
        -Wcast-qual
        -Wcast-align
        -Wformat=2
        -Wundef
        -Wnull-dereference
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wold-style-cast
        -Wzero-as-null-pointer-constant
        -Wdouble-promotion
        -Wimplicit-fallthrough
        -Wreturn-type>
    $<$<CXX_COMPILER_ID:Clang,AppleClang>:
        -Wconditional-uninitialized
        -Wextra-semi
        -Wimplicit-int-conversion
        -Wimplicit-int-float-conversion
        -Wnewline-eof
        -Wshorten-64-to-32
        -Wswitch-enum
        -Wunreachable-code>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches
        -Wduplicated-cond
        -Wlogical-op
        -Wsign-compare
        -Wuseless-cast>
)

add_executable(dans_cpp_playground
    app/main.cpp
)
target_link_libraries(dans_cpp_playground PRIVATE
    dans::util
    dans::core
    dans_cpp_playground_warnings
)
target_precompile_headers(dans_cpp_playground PRIVATE
    <dans/pch.hpp>
)
