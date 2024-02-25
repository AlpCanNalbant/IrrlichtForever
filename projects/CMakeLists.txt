cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
cmake_policy(VERSION 3.28)
project(Workspace LANGUAGES CXX)
message("-- Building \"${PROJECT_NAME}\" in ${CMAKE_BUILD_TYPE} mode.")

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(Threads REQUIRED)
find_package(Irrlicht REQUIRED)

set(INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../outputs")
# set(DEPS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../deps)

set_property(GLOBAL PROPERTY WINAPICOMMON_LANGUAGE_VERSION 20)

# add_compile_definitions(__STRICT_ANSI__=1)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../deps/MagicEnum" "${CMAKE_CURRENT_BINARY_DIR}/deps/MagicEnum")
set_property(GLOBAL PROPERTY PAZU_RESOURCE_GENERATOR_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/IrrlichtForever/ResourceGenerator")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../deps/PazuResource" "${CMAKE_CURRENT_BINARY_DIR}/deps/PazuResource")
# add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../deps/Irrlicht" "${CMAKE_CURRENT_BINARY_DIR}/deps/Irrlicht")
# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../deps/irrlicht/include")
add_subdirectory("IrrlichtForever")

if (NOT IRRLICHT_FOREVER_SKIP_SAMPLE)
    add_subdirectory("Sample")
endif()
