/*#include <cassert>*/
/*#include <filesystem>*/
/*#include <iostream>*/
/*#include <optional>*/
/*#include <string>*/

/**/
/*#define STRINGIFY(x) #x*/
/**/
/*namespace fs = std::filesystem;*/
/**/
/*const auto VERSION = "0.0.1";*/
/*const fs::path HOME = std::getenv("HOME");*/
/*const fs::path TEMPLATE_PATH = HOME / ".local/share/cranky/templates";*/
/**/
/*// Globals*/
/*namespace g {*/
/*std::string project_name = "";*/
/*fs::path update_src = "";*/
/*} // namespace g*/
/**/
/*enum class project_lang {*/
/*  uninit,*/
/*  cpp,*/
/*  c,*/
/*};*/
/**/
/*enum class project_type {*/
/*  uninit,*/
/*  console,*/
/*  glfw_opengl,*/
/*};*/
/**/
/*const std::pair<project_lang, const char *> EXT_MAPPINGS[] = {*/
/*    std::make_pair(project_lang::c, "c"),*/
/*    std::make_pair(project_lang::cpp, "cpp"),*/
/*};*/
/**/
/*void ensure_project_config_file() {*/
/*  if (!fs::exists(fs::current_path() / ".cranky")) {*/
/*    auto copy_from = TEMPLATE_PATH / ".cranky";*/
/*    fs::copy_file(copy_from, fs::current_path());*/
/*  }*/
/*}*/
/**/
/*void setup_project(project_lang language, project_type project_type,*/
/*                   std::optional<std::string> project_name = std::nullopt) {*/
/*  ensure_project_config_file();*/
/**/
/*  fs::path copy_from = TEMPLATE_PATH;*/
/**/
/*  switch (language) {*/
/*  case project_lang::c:*/
/*    copy_from /= "c";*/
/*    break;*/
/*  case project_lang::cpp:*/
/*    copy_from /= "cpp";*/
/*    break;*/
/*  default:*/
/*    throw std::runtime_error("Bad Language. Stop.");*/
/*    break;*/
/*  }*/
/**/
/*  switch (project_type) {*/
/*  case project_type::console:*/
/*    copy_from /= "console";*/
/*    break;*/
/*  case project_type::glfw_opengl:*/
/*    copy_from /= "glfw_opengl";*/
/*    break;*/
/*  default:*/
/*    throw std::runtime_error("Bad Project Type. Stop.");*/
/*    break;*/
/*  }*/
/*  copy_from.make_preferred();*/
/*  auto dest_path = std::filesystem::current_path();*/
/*  if (project_name)*/
/*    dest_path /= project_name.value();*/
/*  std::cout << "Copy Path = " << copy_from << "\n";*/
/*  std::cout << "Dest Path = " << dest_path << "\n";*/
/*  std::filesystem::copy(copy_from, dest_path,*/
/*                        std::filesystem::copy_options::recursive);*/
/*}*/
/**/
/*std::pair<project_lang, project_type> get_project_args() {*/
/*  std::cout << "Project Language:\n";*/
/*  std::cout << "1. C++\n";*/
/*  std::cout << "2. C\n";*/
/**/
/*  char iput[2];*/
/**/
/*  project_lang lang = project_lang::uninit;*/
/**/
/*  while (lang == project_lang::uninit) {*/
/*    std::cin.getline(iput, 2);*/
/*    switch (iput[0]) {*/
/*    case '1':*/
/*      lang = project_lang::c;*/
/*      break;*/
/**/
/*    case '2':*/
/*      lang = project_lang::cpp;*/
/*      break;*/
/**/
/*    default:*/
/*      lang = project_lang::uninit;*/
/*      break;*/
/*    }*/
/*  }*/
/**/
/*  project_type project_t = project_type::uninit;*/
/**/
/*  std::cout << "Project Type:\n";*/
/*  std::cout << "1. Console\n";*/
/*  std::cout << "2. GLFW /w GLAD Windowed\n";*/
/**/
/*  while (project_t == project_type::uninit) {*/
/*    std::cin.getline(iput, 2);*/
/**/
/*    switch (iput[0]) {*/
/*    case '1':*/
/*      project_t = project_type::console;*/
/*      break;*/
/*    case '2':*/
/*      project_t = project_type::glfw_opengl;*/
/*      break;*/
/*    default:*/
/*      project_t = project_type::uninit;*/
/*      break;*/
/*    }*/
/*  }*/
/*  return {lang, project_t};*/
/*}*/

/*int*/
/*handle_command(command ct)*/
/*{*/
/*    switch (ct) {*/
/*        case command::init:*/
/*        case command::create: {*/
/*            auto args = get_project_args();*/
/*            setup_project(args.first, args.second, g::project_name);*/
/*            break;*/
/*        }*/
/*        case command::add:*/
/*            break;*/
/*        case command::remove:*/
/*            break;*/
/*        case command::help:*/
/*        case command::invalid:*/
/*            show_help();*/
/*            return 1;*/
/*            break;*/
/*    }*/
/*    return 0;*/
/*};*/
#include "../inc/args.hpp"

int main(int argc, char **argv) {
  /*command ct = parse_args(argc, argv);*/
  /*return handle_command(ct);*/
  Command command(argc, argv);

  return 0;
}
