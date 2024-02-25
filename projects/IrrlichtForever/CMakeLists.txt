set(IRRLICHT_FOREVER_VERSION 1.0)
project(IrrlichtForever VERSION ${IRRLICHT_FOREVER_VERSION} LANGUAGES CXX)

file(GLOB_RECURSE IRRLICHT_FOREVER_HEADERS CONFIGURE_DEPENDS **.hpp **.inl)
list(REMOVE_ITEM IRRLICHT_FOREVER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.hpp")
file(GLOB_RECURSE IRRLICHT_FOREVER_SOURCES CONFIGURE_DEPENDS **.cpp)

add_library(${PROJECT_NAME} STATIC ${IRRLICHT_FOREVER_HEADERS} ${IRRLICHT_FOREVER_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CMAKE_CXX_EXTENSIONS OFF
	OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${MAGIC_ENUM_INCLUDE_DIRS} INTERFACE ${INSTALL_DIR}/include)
target_precompile_headers(${PROJECT_NAME} PUBLIC "Precompiled.hpp")

# Allow only static linking and we don't want joystick support. Use '-DNO_IRR_COMPILE_WITH_DIRECT3D_9_' if you don't want support Direct3D 9 backend.
set(IRRLICHT_FOREVER_DEFINITIONS -D_UNICODE;-DUNICODE;-D_IRR_STATIC_LIB_;-DNO_IRR_COMPILE_WITH_DIRECTINPUT_JOYSTICK_) # -D__STRICT_ANSI__
set(IRRLICHT_FOREVER_DEBUG_DEFINITIONS ${IRRLICHT_FOREVER_DEFINITIONS};-D_DEBUG)
set(IRRLICHT_FOREVER_RELEASE_DEFINITIONS ${IRRLICHT_FOREVER_DEFINITIONS};-DNDEBUG)

set(IRRLICHT_FOREVER_OPTIONS -m64;-std=c++23;-municode)
# WarningOptionsForGCC: -Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-Wpedantic
# WarningOptionsForClang: -Weverything
set(IRRLICHT_FOREVER_DEBUG_OPTIONS ${IRRLICHT_FOREVER_OPTIONS};-O0;-g3;-Wfatal-errors;-ggdb;-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-Wpedantic;-fext-numeric-literals)
# Disable via exceptions via -fno-exceptions but remember, even exceptions are disabled functions are not automatically marked as noexcept.
# Compiler is not allowed to do such modifications/optimizations.
set(IRRLICHT_FOREVER_RELEASE_OPTIONS ${IRRLICHT_FOREVER_OPTIONS};-fno-exceptions;-Ofast;-s)

target_compile_definitions(${PROJECT_NAME} PUBLIC $<IF:$<CONFIG:Debug>,${IRRLICHT_FOREVER_DEBUG_DEFINITIONS},${IRRLICHT_FOREVER_RELEASE_DEFINITIONS}>)
target_compile_options(${PROJECT_NAME} PUBLIC $<IF:$<CONFIG:Debug>,${IRRLICHT_FOREVER_DEBUG_OPTIONS},${IRRLICHT_FOREVER_RELEASE_OPTIONS}>)
target_link_options(${PROJECT_NAME} PUBLIC -Wl,--subsystem,windows)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		PazuResource Irrlicht
	INTERFACE
		opengl32 winmm stdc++ Threads::Threads)

file(COPY .
	DESTINATION
		${INSTALL_DIR}/include/IrrlichtForever
	FILES_MATCHING
		PATTERN "*.hpp" PATTERN "*.inl"
		PATTERN "ResourceGenerator" EXCLUDE
		PATTERN "Precompiled.hpp" EXCLUDE)
# target_sources(${PROJECT_NAME} PUBLIC FILE_SET irrlicht_forever_headers TYPE HEADERS FILES ${IRRLICHT_FOREVER_HEADERS})
install(TARGETS
        IrrlichtForever
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
    ARCHIVE
        COMPONENT Development
        DESTINATION ${INSTALL_DIR}/obj/${CMAKE_BUILD_TYPE})
    # FILE_SET irrlicht_forever_headers
    #     COMPONENT Development
    #     DESTINATION ${INSTALL_DIR}/include/IrrlichtForever)
