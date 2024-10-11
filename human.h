#ifndef BATTLESHIP__HUMAN_H_
#define BATTLESHIP__HUMAN_H_

#include "player_setup.h"
#include "random.h"

namespace Battleship {

  class human : public player {
   public:
    explicit human(std::string& player_name) {
      name = player_name;
      set_player_board();
    }
    static std::string giving_player_name(int player_num);
    static void game_set_up(human& the_player);
    static void get_two_ints(const std::string& prompt, int& num1, int& num2);
    static std::string get_valid_string(const std::string& prompt);
    static void fight_til_death(human& player1, human& player2);

    char get_position(const char& ship_name);
    void ask_fire_coord(int& r, int& c) override;
  };
}

#endif //BATTLESHIP__HUMAN_H_
