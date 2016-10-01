cmake_minimum_required (VERSION 3.1)

project (xe CXX)
set (xe_VERSION_MAJOR 0)
set (xe_VERSION_MINOR 0)
set (CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS_GPERF
    "${CMAKE_CXX_FLAGS_DEBUG} -pg")
set (CMAKE_C_FLAGS_GPERF
    "${CMAKE_C_FLAGS_DEBUG} -pg")
set (CMAKE_EXE_LINKER_FLAGS_GPERF
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pg")
set (CMAKE_SHARED_LINKER_FLAGS_GPERF
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -pg")
mark_as_advanced (
    CMAKE_CXX_FLAGS_GPERF
    CMAKE_C_FLAGS_GPERF
    CMAKE_EXE_LINKER_FLAGS_GPERF
    CMAKE_SHARED_LINKER_FLAGS_GPERF)


find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)
find_library (SOIL_LIBRARIES NAMES SOIL Soil soil)
find_path (SOIL_INCLUDE_DIRS SOIL.h PATH_SUFFIXES SOIL HINTS "/usr/local/include")
find_library (YAML_CPP_LIBRARIES NAMES yaml-cpp)
find_path (YAML_CPP_INCLUDE_DIRS yaml.h PATH_SUFFIXES yaml-cpp HINTS "/usr/local/include" "/usr/include")
find_package (Lua)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SOIL_INCLUDE_DIRS})
include_directories(${YAML_CPP_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIRS})

add_subdirectory(deps/imgui)
include_directories(deps/imgui)
include_directories(deps/glm)
include_directories(deps/spdlog/include)
include_directories(deps/sol2)
include_directories(deps/IconFontCppHeaders)
include_directories(deps/filesystem)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(xe main.cpp gui.cpp shaders.cpp scenegraph.cpp scene.cpp
    renderer.cpp gameobject.cpp cube.cpp camera.cpp texture.cpp services/input.cpp
    services/locator.cpp services/resources.cpp behavior.cpp ui/theme.cpp)

target_link_libraries(xe ${OPENGL_LIBRARIES})
target_link_libraries(xe ${GLFW_LIBRARIES})
target_link_libraries(xe ${GLEW_LIBRARIES})
target_link_libraries(xe ${SOIL_LIBRARIES})
target_link_libraries(xe ${YAML_CPP_LIBRARIES})
target_link_libraries(xe ${LUA_LIBRARIES})
target_link_libraries(xe imgui)

