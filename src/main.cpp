#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Get ready for the worst code you've ever seen

std::vector<std::string> glfw_opengl_main_cpp = {
    "#include <cstdio>\n",
    "#include <glad/glad.h>\n",
    "#include <GLFW/glfw3.h>\n",
    "\n",
    "void handle_events(GLFWwindow* window) {\n",
    "if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {\n",
    "glfwSetWindowShouldClose(window, GLFW_TRUE);\n",
    "}\n",
    "}\n",
    "\n",
    "void on_window_resize(GLFWwindow* window, int width, int height) {\n",
    "glViewport(0, 0, width, height);\n",
    "}\n",
    "\n",
    "int main(void) {\n",
    "\n",
    "if (!glfwInit()) {\n",
    "return 1;\n",
    "}\n",
    "\n",
    "glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\n",
    "glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\n",
    "glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);\n",
    "glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);\n",
    "\n",
    "auto window = glfwCreateWindow(800, 600, \"Window\", nullptr, nullptr);\n",
    "if (window == nullptr) {\n",
    "printf(\"Couldn't make window!\\n\");\n",
    "return 1;\n",
    "}\n",
    "\n",
    "glfwSetWindowSizeCallback(window, on_window_resize);\n",
    "\n",
    "glfwMakeContextCurrent(window);\n",
    "int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);\n",
    "\n",
    "while (!glfwWindowShouldClose(window)) {\n",
    "glClearColor(0.3, 0.6, 0.4, 1.0);\n",
    "glClear(GL_COLOR_BUFFER_BIT);\n",
    "glfwPollEvents();\n",
    "handle_events(window);\n",
    "glfwSwapBuffers(window);\n",
    "}\n",
    "\n",
    "glfwTerminate();\n",
    "\n",
    "return 0;\n",
    "}\n"};

std::vector<std::string> glfw_opengl_cmakelists_txt = {
    "cmake_minimum_required(VERSION 3.29)\n",
    "project(out)\n",
    "\n",
    "set(CMAKE_CXX_STANDARD 20)\n",
    "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n",
    "\n",
    "include(FetchContent)\n",
    R"(FETCHCONTENT_DECLARE(GLFW GIT_REPOSITORY https://github.com/glfw/glfw.git))",
    "\nFETCHCONTENT_MAKEAVAILABLE(GLFW)\n",
    R"(FETCHCONTENT_DECLARE(GLAD GIT_REPOSITORY https://github.com/Dav1dde/glad.git))",
    "\nFETCHCONTENT_MAKEAVAILABLE(GLAD)\n",
    "\n",
    "set(PROJ_INCLUDE_DIR \"include\")\n",
    "set(PROJ_DEPENDS_DIR \"deps\")\n",
    "\n",
    "find_package(OpenGL REQUIRED)\n",
    "\n",
    "add_executable(out src/main.cpp)\n",
    "\n",
    "target_link_libraries(out glad opengl32 glfw)\n",
    "target_include_directories(out PUBLIC \"${PROJ_INCLUDE_DIR}\")\n",
    "\n",
    "add_custom_target(run\n",
    "COMMAND ${CMAKE_CURRENT_BINARY_DIR}/out\n",
    "WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}\n",
    "DEPENDS out\n",
    ")\n"};

std::vector<std::string> default_main_cpp = {
    "#include <cstdio>\n", "\n",
    "int main(void) {\n",  "printf(\"Hello, World\\n\");\n",
    "return 0;\n",         "}\n"};

std::vector<std::string> default_clang_format = {
    "BasedOnStyle: LLVM\n", "DerivePointerAlignment: false\n",
    "PointerAlignment: Left\n", "IndentWidth: 4\n", "SortIncludes: false\n"};

std::vector<std::string> default_cmakelists_txt = {
    "cmake_minimum_required(VERSION 3.29)\n",
    "project(out)\n",
    "\n",
    "set(CMAKE_CXX_STANDARD 20)\n",
    "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n",
    "\n",
    "add_executable(out src/main.cpp)\n",
    "\n",
    "set(PROJ_INCLUDE_DIR include)\n",
    "set(PROJ_DEPENDS_DIR deps)\n",
    "\n",
    "add_custom_target(run\n",
    "COMMAND ${CMAKE_CURRENT_BINARY_DIR}/out\n",
    "WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}\n",
    "DEPENDS out\n",
    ")\n"};

std::vector<std::string> default_preload_cmake = {
    "set(CMAKE_GENERATOR \"Unix Makefiles\" CACHE INTERNAL \"\")"};

enum language {
  cpp,
  c,
};

enum project_type {
  console,
  windowed,
};

void setup_project(language language, project_type project_type,
                   std::string project_name) {
  std::vector<std::string> &default_main = default_main_cpp;
  std::vector<std::string> &default_cmake = default_cmakelists_txt;
  const std::vector<std::string> &default_cmake_pre = default_preload_cmake;
  const std::vector<std::string> &default_clang = default_clang_format;
  std::string main_file_name = "main.cpp";

  if (project_type != console) {
    default_cmake = glfw_opengl_cmakelists_txt;
    default_main = glfw_opengl_main_cpp;
  }

  if (language != cpp) {
    default_cmake[3] = "set(CMAKE_C_STANDARD 23)\n";
    default_cmake.at(default_cmake.size() - 10) =
        "add_executable(out src/main.c)\n";
    default_main[0] = "#include <stdio.h>\n";
    main_file_name = "main.c";
  }

  std::filesystem::create_directory(project_name);
  std::filesystem::current_path(project_name);
  std::cout << "Project Directory Created\n";

  std::filesystem::create_directory("build");
  std::filesystem::create_directory("src");
  std::filesystem::create_directory("res");
  std::cout << "Subdirectories created\n";

  std::fstream f;

  f.open(".clang-format", std::ios::app);
  for (const auto &line : default_clang) {
    f.write(line.c_str(), line.size());
  }
  f.close();
  std::cout << "Clang Format Config written\n";

  f.open("PreLoad.cmake", std::ios::app);
  for (const auto &line : default_cmake_pre) {
    f.write(line.c_str(), line.size());
  }
  f.close();

  std::cout << "CMake Preload written\n";

  f.open("CMakeLists.txt", std::ios::app);
  for (const auto &line : default_cmake) {
    f.write(line.c_str(), line.size());
  }
  f.close();
  std::cout << "CMake file written\n";

  f.open("src/" + main_file_name, std::ios::app);
  for (const auto &line : default_main_cpp) {
    f.write(line.c_str(), line.size());
  }
  f.close();
  std::cout << "Main file written\n";
}

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cerr << "INFO:\nUsage: rank [PROJECT NAME]\n";
    return 1;
  }

  std::cout << "Project Language:\n";
  std::cout << "1. C++ [Default]\n";
  std::cout << "2. C\n";

  char iput[2];
  std::cin.getline(iput, 2);

  language lang;
  switch (iput[0]) {
  case '2':
    lang = c;
    break;

  default:
    lang = cpp;
    break;
  }

  project_type project_t;

  std::cout << "Project Type:\n";
  std::cout << "1. Console [Default]\n";
  std::cout << "2. GLFW /w GLAD Windowed\n";

  std::cin.getline(iput, 2);

  switch (iput[0]) {
  case '2':
    project_t = windowed;
    break;

  default:
    project_t = console;
    break;
  }

  std::cout << "Project Name = " << argv[1] << "\n";

  setup_project(lang, project_t, argv[1]);

  return 0;
}
