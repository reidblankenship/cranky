#ifndef CRANKY_ARGS_H
#define CRANKY_ARGS_H

#include <optional>
#include <string>
#include <vector>

enum class command_t {
    invalid = -1,
    help = 0,
    new_project = 1,
};

typedef std::string cranky_arg_lhs;
typedef std::optional<std::string> cranky_arg_rhs;
typedef std::pair<cranky_arg_lhs, cranky_arg_rhs> cranky_arg_type;
typedef std::vector<cranky_arg_type> cranky_vec_args;

class Command {
  public:
    static cranky_vec_args parse_exec(int argc, char **argv);
    void print_args(const cranky_vec_args& args) const;
};

#endif // CRANKY_ARGS_H
