#include "../inc/project.hpp"
#include <filesystem>
#include <iostream>
#include <optional>

namespace fs = std::filesystem;

const auto VERSION = "0.0.1";
const fs::path HOME = std::getenv("HOME");
const fs::path TEMPLATE_PATH = HOME / ".local/share/cranky/templates";

// Globals
namespace g {
std::string project_name = "";
fs::path update_src = "";
} // namespace g

enum class project_lang {
  uninit,
  cpp,
  c,
};

enum class project_type {
  uninit,
  console,
  glfw_opengl,
};

void setup_project(project_lang language, project_type project_type,
                   std::optional<std::string> project_name = std::nullopt) {
  /*ensure_project_config_file();*/

  fs::path copy_from = TEMPLATE_PATH;

  switch (language) {
  case project_lang::c:
    copy_from /= "c";
    break;
  case project_lang::cpp:
    copy_from /= "cpp";
    break;
  default:
    throw std::runtime_error("Bad Language. Stop.");
    break;
  }

  switch (project_type) {
  case project_type::console:
    copy_from /= "console";
    break;
  case project_type::glfw_opengl:
    copy_from /= "glfw_opengl";
    break;
  default:
    throw std::runtime_error("Bad Project Type. Stop.");
    break;
  }
  copy_from.make_preferred();
  auto dest_path = std::filesystem::current_path();
  if (project_name)
    dest_path /= project_name.value();
  std::cout << "Copy Path = " << copy_from << "\n";
  std::cout << "Dest Path = " << dest_path << "\n";
  std::filesystem::copy(copy_from, dest_path,
                        std::filesystem::copy_options::recursive);
}

std::pair<project_lang, project_type> get_project_args() {
  std::cout << "Project Language:\n";
  std::cout << "1. C++\n";
  std::cout << "2. C\n";

  char iput[2];

  project_lang lang = project_lang::uninit;

  while (lang == project_lang::uninit) {
    std::cin.getline(iput, 2);
    switch (iput[0]) {
    case '1':
      lang = project_lang::c;
      break;

    case '2':
      lang = project_lang::cpp;
      break;

    default:
      lang = project_lang::uninit;
      break;
    }
  }

  project_type project_t = project_type::uninit;

  std::cout << "Project Type:\n";
  std::cout << "1. Console\n";
  std::cout << "2. GLFW /w GLAD Windowed\n";

  while (project_t == project_type::uninit) {
    std::cin.getline(iput, 2);

    switch (iput[0]) {
    case '1':
      project_t = project_type::console;
      break;
    case '2':
      project_t = project_type::glfw_opengl;
      break;
    default:
      project_t = project_type::uninit;
      break;
    }
  }
  return {lang, project_t};
}

void init_project() {
    auto args = get_project_args();
    setup_project(args.first, args.second);
}

void new_project(const char* project_name) {
    auto args = get_project_args();
    setup_project(args.first, args.second, project_name);
}
