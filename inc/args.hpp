#ifndef CRANKY_ARGS_H
#define CRANKY_ARGS_H

#include <string>
#include <vector>

enum class command_t {
    invalid = -1,
    help = 0,
    new_project = 1,
};

class Command {
  public:
    Command(int argc, char **argv);
    static command_t ParseCommand(const std::vector<std::string>& what);

  private:
};

#endif // CRANKY_ARGS_H
