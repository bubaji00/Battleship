
#ifndef BATTLESHIP__MODE_H_
#define BATTLESHIP__MODE_H_

#include "random.h"
#include "AI.h"
namespace Battleship {
  int select_mode();
  int select_ai();
  int get_valid_int(const std::string &prompt);
  void human_vs_human();
  void human_vs_ai();
  void ai_involved(int& mode);
  void ai_vs_ai(int first_ai_type);

  template<class first_player, class second_player>
  void something_vs_something  (first_player& player1, second_player& player2);
}
#endif //BATTLESHIP__MODE_H_
