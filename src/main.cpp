#include <filesystem>
#include <iostream>
#include <string>

const auto VERSION = "0.0.1";
const std::filesystem::path HOME = std::getenv("HOME");
const std::filesystem::path templ_path = HOME / ".local/share/cranky/templates";

enum language {
  cpp,
  c,
};

enum project_type {
  console,
  glfw_opengl,
};

void setup_project(language language, project_type project_type,
                   std::string project_name) {
  std::string main_file_name = "main.c";
  std::filesystem::path copy_path = templ_path;

  switch (language) {
  case c:
    copy_path.append("c");
    break;
  case cpp:
    copy_path.append("cpp");
    main_file_name.append("pp");
    break;
  }

  switch (project_type) {
  case console:
    copy_path.append("console");
    break;
  case glfw_opengl:
    copy_path.append("glfw_opengl");
    break;
  }
  copy_path = copy_path.make_preferred();
  const auto dest_path = std::filesystem::current_path() / project_name;
  std::cout << "Preferred Copy Path = " << copy_path << "\n";
  std::cout << "Preferred Dest Path = " << dest_path << "\n";
  std::filesystem::copy(copy_path, dest_path,
                        std::filesystem::copy_options::recursive);
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
    project_t = glfw_opengl;
    break;

  default:
    project_t = console;
    break;
  }

  std::cout << "Project Name = " << argv[1] << "\n";

  setup_project(lang, project_t, argv[1]);

  return 0;
}
