#include "AI.h"
#include "read_file.h"
std::mt19937 Battleship::AI_Player::gen(time(nullptr));

void Battleship::cheating_AI::ask_fire_coord(int &r, int &c) {
  for (int rows = 0; rows < config::return_rows(); ++rows) {
    for (int col = 0; col < config::return_col(); ++col) {
      if (oppo_placement_board[rows][col] != '*') {
        oppo_placement_board[rows][col] = '*';
        r = rows;
        c = col;
        return;
      }
    }
  }
}

void Battleship::random_AI::ask_fire_coord(int &r, int &c) {
  random_r_c_gen(r, c);
}

void Battleship::hunt_destroy::ask_fire_coord(int& r, int& c) {
  if (hit_status) {
    if (check_fire_valid(last_hit_coord.first, last_hit_coord.second-1)) {
      next_move.emplace_back(last_hit_coord.first, last_hit_coord.second-1);
    }
    if (check_fire_valid(last_hit_coord.first-1, last_hit_coord.second)) {
      next_move.emplace_back(last_hit_coord.first-1, last_hit_coord.second);
    }
    if (check_fire_valid(last_hit_coord.first, last_hit_coord.second+1)) {
      next_move.emplace_back(last_hit_coord.first, last_hit_coord.second+1);
    }
    if (check_fire_valid(last_hit_coord.first+1, last_hit_coord.second)) {
      next_move.emplace_back(last_hit_coord.first+1, last_hit_coord.second);
    }
    hit_status = false;
  }
  if (!next_move.empty()) {
    r = next_move.at(0).first;
    c = next_move.at(0).second;

    for (auto i = locations_to_fire.begin(); i < locations_to_fire.end(); ++i) {
      if (r == i->first && c == i->second) {
        locations_to_fire.erase(i);
      }
    }

    next_move.erase(next_move.begin());
  } else { random_r_c_gen(r, c); }
}

bool Battleship::hunt_destroy::check_fire_valid(const int& r, const int& c) {
  return !(r < 0 || c < 0 || r >= config::return_rows() || c >= config::return_col()) && fire_board[r][c]!='X' &&
      fire_board[r][c]!='O';
}

void Battleship::random_AI::random_r_c_gen(int& r, int& c) {
  int location = create_random_num(locations_to_fire.size() - 1);
  r = locations_to_fire.at(location).first;
  c = locations_to_fire.at(location).second;
  locations_to_fire.erase(locations_to_fire.begin()+location);
}

void Battleship::random_AI::coord_board_initialization() {
  for (int rows = 0; rows < config::return_rows(); ++rows) {
    for (int col = 0; col < config::return_col(); ++col) {
      locations_to_fire.emplace_back(rows, col);
    }
  }
}

void Battleship::AI_Player::set_up_ai() {
  int r, c, temp_pos;
  char position;

  for (const auto& the_ships : Battleship::config::return_ships()) {
    do {
      temp_pos = Battleship::AI_Player::create_random_num (1);
      if (temp_pos == 0) {
        position = 'h';
        r = Battleship::AI_Player::create_random_num (Battleship::config::return_rows()-1);
        c = Battleship::AI_Player::create_random_num (Battleship::config::return_col() - the_ships.second);
      } else if (temp_pos == 1) {
        position = 'v';
        r = Battleship::AI_Player::create_random_num (Battleship::config::return_rows()- the_ships.second);
        c = Battleship::AI_Player::create_random_num (Battleship::config::return_col() - 1);
      }

    } while (!checking_valid_r_c(r, c, the_ships, position));
    place_ship(the_ships, position, r, c);
    std::cout << name << "'s Board" << std::endl;
    print_og_board();
    std::cout << std::endl;
  }
}

int Battleship::AI_Player::create_random_num (int max_range) {
  std::uniform_int_distribution<int> the_range(0,max_range);
  return the_range(gen);
}