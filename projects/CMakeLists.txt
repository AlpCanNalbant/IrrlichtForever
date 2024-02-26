set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

add_subdirectory("IrrlichtForever")

if (NOT IRRLICHT_FOREVER_SKIP_SAMPLE)
    add_subdirectory("Sample")
endif()
