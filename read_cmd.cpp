#include "read_cmd.h"

std::string Battleship::cmd_storing::file_name;
bool Battleship::cmd_storing::seed_status;
int Battleship::cmd_storing::seed;

Battleship::cmd_storing::cmd_storing(int argc, char *argv[]) {
  if (argc > 2) {
    seed_status = true;
    seed = std::stoi(argv[2]);
    file_name = argv[1];

  } else if (argc == 2) {
    file_name = argv[1];
    seed_status = false;

  } else {
    std::cout << "Expected command line input, program aborted." << std::endl;
    exit(1);
  }
}