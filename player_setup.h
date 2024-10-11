#ifndef BATTLESHIP__PLAYER_SETUP_H_
#define BATTLESHIP__PLAYER_SETUP_H_

#include "random.h"
#include "read_file.h"
namespace Battleship {
  class player {
   public:
    bool hit_status;
    std::pair<int, int> last_hit_coord;
    std::vector<char> set_cols;
    std::vector<std::vector<char>> set_board;
    std::vector<std::vector<char>> fire_board;
    std::string name;

    void set_player_board() {
      for (int j = 0; j < Battleship::config::return_col(); ++j) {
        set_cols.push_back('*');
      }
      for (int i = 0; i < Battleship::config::return_rows(); ++i) {
        set_board.push_back(set_cols);
        fire_board.push_back(set_cols);
      }
    }

    void print_both_boards(const std::string& player_name) const;
    void print_og_board() const;
    void print_fire_board() const;
    bool check_result(const std::string& winner_name);
    void place_ship(std::pair<char, int> ship, char position, int r, int c);
    bool checking_valid_r_c(int r, int c, std::pair<char, int> ship, char position);

    virtual bool check_fire_valid(const int& r, const int& c);
    virtual void modify_boards(player& opp_player, int r, int c);
    virtual void ask_fire_coord(int& r, int& c) {}
  };
}
#endif //BATTLESHIP__PLAYER_SETUP_H_