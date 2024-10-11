#include "read_cmd.h"
#include "read_file.h"
#include "mode.h"
#include "AI.h"

int main(int argc, char* argv[]) {
  Battleship::cmd_storing(argc, argv);
  Battleship::config();
  int mode = Battleship::select_mode();

  if (mode == 1) {
    Battleship::human_vs_human(); // human only, no random needed.
  } else {

      if (Battleship::cmd_storing::seed_status) {
        Battleship::AI_Player::gen.seed(Battleship::cmd_storing::seed);
      } else {
        Battleship::AI_Player::gen.seed(time(nullptr));
      }
    Battleship::ai_involved(mode);
  }
  return 0;
}