
#include "../inc/args.hpp"
#include "../inc/project.hpp"

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#define CRANKY_VERSION "0.0.2"

#define eprintln(fmt...)                                                       \
    fprintf(stderr, fmt);                                                      \
    fprintf(stderr, "\n");

#define println(fmt...)                                                        \
    printf(fmt);                                                               \
    printf("\n");

#define breakln() printf("\n");

#define print_vec(vec, elem_t)                                                 \
    std::copy(std::begin(vec), std::end(vec),                                  \
              std::ostream_iterator<elem_t>(std::cout, " "));                  \
    breakln()

// clang-format off
const std::map<std::string, const char *> help_table = {
    std::make_pair("help",
                   "Usage: cranky help [COMMAND]\n"
                   "Help information for specific command.\n"
                   "Without [COMMAND], displays all help info.\n"),

    std::make_pair("version",
                   "Usage: cranky version\n"
                   "Shows version info.\n"),

    std::make_pair("new",
                   "Usage: cranky new [PROJECT NAME]\n"
                   "Creates a new project in a new directory called [PROJECT NAME].\n"
                   "Project Configuration options are prompted.\n"),

    std::make_pair("init",
                   "Usage: cranky init\n"
                   "Creates a new project in the current directory.\n"
                   "Project Configuration options are prompted.\n"),
};
// clang-format on

void show_version() {
    println("cranky Version: %s", CRANKY_VERSION);
}

void show_help() {
    println("Usage: cranky [COMMAND] [OPTIONS]\n"
            "By default, shows help information for multiple commands.\n");
    for (const auto &h : help_table) {
        println("%s", h.second);
    }
}

void show_help_with(const char *with) {
    if (strcmp(with, "") == 0) {
        show_help();
        return;
    }
    const auto &help = help_table.find(with);
    if (help == help_table.end()) {
        show_help();
        println("No valid command found for: \"%s\".", with);
        return;
    }
    println("%s", help->second);
}

const std::unordered_map<std::string, size_t> ALL_CMDS_OPTS = {
    std::make_pair("init", 0),
    std::make_pair("version", 0),
    std::make_pair("help", 0),
    std::make_pair("help", 1),
    std::make_pair("new", 1),
};

const std::unordered_map<std::string, std::function<void(const char *)>>
    CMD_ONE_OPT = {
        std::make_pair("new", new_project),
        std::make_pair("help", show_help_with),
};

const std::unordered_map<std::string, std::function<void()>> CMD_NO_OPT = {
    std::make_pair("init", init_project),
    std::make_pair("version", show_version),
    std::make_pair("help", show_help),
};

cranky_vec_args cmd_vec(int argc, char **argv) {
    cranky_vec_args ret{};
    const auto &FIRST_ARG = argv[1];
    const auto &SECOND_ARG = argv[2];
    const auto &cmd_no_options = CMD_NO_OPT.contains(FIRST_ARG) && argc == 2;
    const auto &cmd_one_option = (CMD_ONE_OPT.contains(FIRST_ARG) &&
                                  (SECOND_ARG != nullptr) && argc == 3);

    if (cmd_no_options) {
        ret.emplace_back(FIRST_ARG, std::nullopt);
    } else if (cmd_one_option) {
        ret.emplace_back(FIRST_ARG,
                         std::make_optional<std::string>(SECOND_ARG));
    } else {
        show_help_with(FIRST_ARG);
        exit(1);
    }
    return ret;
}

void Command::print_args(const cranky_vec_args& args) const {
    size_t i = 0;
    for (auto cmd = args.begin(); cmd != args.end(); cmd++) {
        println(
            "cmd[%zu].first = %s, .second = %s", i, cmd->first.c_str(),
            (cmd->second.has_value() ? cmd->second.value() : "None").c_str());
        i++;
    }
}

cranky_vec_args Command::parse_exec(int argc, char **argv) {
    cranky_vec_args args{};
    if (argc == 1) {
        show_help();
        exit(1);
    }
    args = cmd_vec(argc, argv);
    if (args.front().second.has_value()) {
        CMD_ONE_OPT.at(args.front().first)(args.front().second.value().c_str());
    } else {
        CMD_NO_OPT.at(args.front().first)();
    }
    return args;
}
