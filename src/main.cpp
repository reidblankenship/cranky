#include "../inc/args.hpp"

int main(int argc, char **argv) {
    Command::parse_exec(argc, argv);

    return 0;
}
