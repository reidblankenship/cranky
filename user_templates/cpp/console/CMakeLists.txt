cmake_minimum_required(VERSION 3.28)
project(out)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(out src/main.cpp)

set(PROJ_INCLUDE_DIR include)
set(PROJ_DEPENDS_DIR deps)

add_custom_target(run
COMMAND ${CMAKE_CURRENT_BINARY_DIR}/out
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
DEPENDS out
)
