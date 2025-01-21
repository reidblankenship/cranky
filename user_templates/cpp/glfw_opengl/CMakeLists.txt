cmake_minimum_required(VERSION 3.28)
project(out)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FETCHCONTENT_DECLARE(GLFW GIT_REPOSITORY https://github.com/glfw/glfw.git)
FETCHCONTENT_MAKEAVAILABLE(GLFW)
FETCHCONTENT_DECLARE(GLAD GIT_REPOSITORY https://github.com/Dav1dde/glad.git)
FETCHCONTENT_MAKEAVAILABLE(GLAD)

set(PROJ_INCLUDE_DIR "include")
set(PROJ_DEPENDS_DIR "deps")

find_package(OpenGL REQUIRED)

add_executable(out src/main.cpp)

if (WIN32)
    # Windows
    target_link_libraries(out glad opengl32 glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux
    target_link_libraries(out glad GL glfw)
else ()
    message(FATAL_ERROR "OpenGL Dependencies For Your Platform Not Yet Supported By Cranky")
endif ()

target_include_directories(out PUBLIC "${PROJ_INCLUDE_DIR}")

add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS out
)
