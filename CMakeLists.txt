cmake_minimum_required (VERSION 3.1)

project (xe CXX)
set (xe_VERSION_MAJOR 0)
set (xe_VERSION_MINOR 0)
set (CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)
find_library (SOIL_LIBRARIES NAMES SOIL Soil soil)
find_path (SOIL_INCLUDE_DIRS SOIL.h PATH_SUFFIXES SOIL HINTS "/usr/local/include")

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SOIL_INCLUDE_DIRS})

add_subdirectory(imgui)
include_directories(imgui)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(xe main.cpp gui.cpp shaders.cpp)

target_link_libraries(xe ${OPENGL_LIBRARIES})
target_link_libraries(xe ${GLFW_LIBRARIES})
target_link_libraries(xe ${GLEW_LIBRARIES})
target_link_libraries(xe ${SOIL_LIBRARIES})
target_link_libraries(xe imgui)

add_custom_command(TARGET xe PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:xe>/shaders)

