#ifndef BATTLESHIP__AI_H_
#define BATTLESHIP__AI_H_

#include "random.h"
#include "player_setup.h"
#include "read_cmd.h"

namespace Battleship {
  class AI_Player : public player {
   public:
    static std::mt19937 gen;

    static int create_random_num (int max_range);
    void set_up_ai();
  };
  class cheating_AI : public AI_Player {
   public:
    std::vector<std::vector<char>> oppo_placement_board;

    explicit cheating_AI(std::string& name, const std::vector<std::vector<char>>& op_placement) {
      this->name = name;
      oppo_placement_board = op_placement;
      set_player_board();
      set_up_ai();
    }
    explicit cheating_AI(std::string& name) {
      this->name = name;
      set_player_board();
      set_up_ai();
    }
    void ask_fire_coord(int& r, int& c) override;
  };

  class random_AI : public AI_Player {
   public:
    std::vector<std::pair<int, int>> locations_to_fire;
    explicit random_AI(std::string& name) {
      this->name = name;
      set_player_board();
      set_up_ai();
      coord_board_initialization();
    }
    void random_r_c_gen(int& r, int& c);
    void ask_fire_coord(int& r, int& c) override;
    void coord_board_initialization();
  };


  class hunt_destroy : public random_AI {
   public:
    std::vector<std::pair<int, int>> next_move;
    explicit hunt_destroy(std::string& name) : random_AI(name) {
    }
    bool check_fire_valid(const int& r, const int& c) override;
    void ask_fire_coord(int& r, int& c) override;
  };
}
#endif //BATTLESHIP__AI_H_