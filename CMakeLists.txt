cmake_minimum_required(VERSION 3.28)
project(cranky)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJ_INCLUDE_DIR "include")
set(PROJ_DEPENDS_DIR "deps")

add_executable(cranky src/main.cpp src/args.cpp src/project.cpp)

add_custom_target(run
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/cranky
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS cranky
)
