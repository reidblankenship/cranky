
#include "../inc/args.hpp"
#include "../inc/project.hpp"

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#define println(fmt...)                                                        \
    printf(fmt);                                                               \
    printf("\n");

// clang-format off
const std::map<std::string, const char *> help_table = {
    std::make_pair("help",
                   "Usage: cranky help [COMMAND]\n"
                   "Help information for specific command.\n"),

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
        println("No help options found for \"%s\". Sorry.", with);
        return;
    }
    println("%s", help->second);
}

const std::unordered_map<std::string, size_t> COMMAND_NUM_OPTS = {
    std::make_pair("init", 0),
    std::make_pair("help", 1),
    std::make_pair("new", 1),
};

const std::unordered_map<std::string, std::function<void(const char *)>>
    COMMAND_ONE_OPT = {
        std::make_pair("new", new_project),
        std::make_pair("help", show_help_with),
};

const std::unordered_map<std::string, std::function<void()>> COMMAND_NO_OPT = {
    std::make_pair("init", init_project),
};

bool check_conflicting_commands(const std::set<std::string> &commands_used) {
    return (commands_used.contains("init") &&
            (commands_used.contains("new") || commands_used.contains("help")));
}

Command::Command(int argc, char **argv) {
    std::set<std::string> commands_used;
    std::vector<std::string> foo;
    if (argc == 1) {
        show_help();
        return;
    }
    for (int i = 1; i < argc; i++) {
        if (check_conflicting_commands(commands_used)) {
            println("Conflicting commands.");
            show_help();
            exit(2);
        }
        if (commands_used.find(argv[i]) != commands_used.end()) {
            println("Can't use the same command multiple times.");
            size_t idx = 0;
            for (const auto &cmd : commands_used) {
                println("Command %zu = %s", idx, cmd.c_str());
            }
            exit(1);
        }
        const auto &cmd = COMMAND_NUM_OPTS.find(argv[i]);
        if (cmd == COMMAND_NUM_OPTS.end()) {
            exit(420);
        }
        if (!argv[(cmd->second + i)]) {
            println("Command \"%s\" requires %zu options", cmd->first.c_str(),
                    cmd->second);
            exit(69);
        }
        commands_used.insert(cmd->first);
        i += cmd->second;
    }
    for (int i = 1; i < argc; i++) {
        if (COMMAND_NO_OPT.find(argv[i]) != COMMAND_NO_OPT.end()) {
            auto action = COMMAND_NO_OPT.find(argv[i]);
            action->second();
        }
        if (COMMAND_ONE_OPT.find(argv[i]) != COMMAND_ONE_OPT.end()) {
            auto action = COMMAND_ONE_OPT.find(argv[i]);
            action->second(argv[i + 1]);
            i++;
            continue;
        }
    }
}
