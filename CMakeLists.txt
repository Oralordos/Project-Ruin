cmake_minimum_required (VERSION 2.8.0)

project (Ruin)

set (Ruin_VERSION_MAJOR 0)
set (Ruin_VERSION_MINOR 1)

if (UNIX OR APPLE)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX OR APPLE)

configure_file ("${PROJECT_SOURCE_DIR}/RuinConfig.h.in" "${PROJECT_BINARY_DIR}/config/RuinConfig.h")
include_directories ("${PROJECT_BINARY_DIR}/config")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package (SDL2 REQUIRED)
find_package (OpenGL REQUIRED)

file (GLOB INCLUDES include/*.h)
file (GLOB SOURCES src/*.cpp)
add_executable (Ruin WIN32 MACOSX_BUNDLE ${SOURCES} ${INCLUDES})

include_directories ("include")
include_directories (${SDL2_INCLUDE_DIR})
include_directories (${OPENGL_INCLUDE_DIR})
target_link_libraries (Ruin ${SDL2_LIBRARY})
target_link_libraries (Ruin ${OPENGL_LIBRARIES})

if(WIN32)
add_custom_command (TARGET Ruin POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_DLL}"
	$<TARGET_FILE_DIR:Ruin>)
endif(WIN32)

install (TARGETS Ruin RUNTIME DESTINATION "bin")
if(WIN32)
install (FILES ${SDL2_DLL} DESTINATION "bin")
endif(WIN32)

include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${Ruin_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Ruin_VERSION_MINOR}")
include (CPack)
