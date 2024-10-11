#ifndef BATTLESHIP__READ_CMD_H_
#define BATTLESHIP__READ_CMD_H_

#include "random.h"

namespace Battleship {
  class cmd_storing {
   public:
    cmd_storing(int argc, char *argv[]);
    static std::string file_name;
    static bool seed_status;
    static int seed;
  };
}

#endif //BATTLESHIP__READ_CMD_H_
