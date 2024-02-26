# Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

find_package(PkgConfig)
pkg_check_modules(PC_Irrlicht QUIET Irrlicht)

find_path(Irrlicht_INCLUDE_DIR NAMES irrlicht.h PATHS ${PC_Irrlicht_INCLUDE_DIRS} PATH_SUFFIXES irrlicht)
find_library(Irrlicht_LIBRARY NAMES irrlicht PATHS ${PC_Irrlicht_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Irrlicht
    FOUND_VAR
        Irrlicht_FOUND
    REQUIRED_VARS
        Irrlicht_LIBRARY
        Irrlicht_INCLUDE_DIR)

if (Irrlicht_FOUND)
    set(Irrlicht_LIBRARIES ${Irrlicht_LIBRARY})
    set(Irrlicht_INCLUDE_DIRS ${Irrlicht_INCLUDE_DIR})
    set(Irrlicht_DEFINITIONS ${PC_Irrlicht_CFLAGS_OTHER})
endif()

if (Irrlicht_FOUND AND NOT TARGET Irrlicht::Irrlicht)
    add_library(Irrlicht::Irrlicht UNKNOWN IMPORTED)
    set_target_properties(Irrlicht::Irrlicht PROPERTIES
        IMPORTED_LOCATION "${Irrlicht_LIBRARY}"
        INTERFACE_COMPILE_OPTIONS "${PC_Irrlicht_CFLAGS_OTHER}"
        INTERFACE_INCLUDE_DIRECTORIES "${Irrlicht_INCLUDE_DIR}")
endif()

mark_as_advanced(Irrlicht_INCLUDE_DIR Irrlicht_LIBRARY)
