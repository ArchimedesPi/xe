cmake_minimum_required (VERSION 3.1)

project (xe CXX)
set (xe_VERSION_MAJOR 0)
set (xe_VERSION_MINOR 0)
set (CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)

include_directories ("${PROJECT_SOURCE_DIR}/src")
link_directories ("${PROJECT_SOURCE_DIR}/src")

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

add_subdirectory(imgui)
include_directories(imgui)

add_executable(xe main.cpp gui.cpp)

target_link_libraries(xe ${OPENGL_LIBRARIES})
target_link_libraries(xe ${GLFW_LIBRARIES})
target_link_libraries(xe ${GLEW_LIBRARIES})
target_link_libraries(xe imgui)

