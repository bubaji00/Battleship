#include "random.h"
#include "read_file.h"
#include "player_setup.h"
#include "human.h"

void Battleship::human::fight_til_death(human& player1, human& player2) {
  int r, c;
  do {
    player1.ask_fire_coord(r, c); // ask coord
    player1.modify_boards(player2, r, c);

    bool p1_status = player2.check_result(player1.name);
    if (p1_status) { break; }

    player2.ask_fire_coord(r, c); // ask coord
    player2.modify_boards(player1, r, c);

  } while (!player1.check_result(player2.name));
}

bool Battleship::player::check_result(const std::string& winner_name) {
  for (const auto& rows: set_board) {
    for (const auto& each : rows) {
      if (each != '*' && each != 'O' && each != 'X') {
        return false;
      }
    }
  }
  std::cout << winner_name << " won the game!" << std::endl;
  return true;
}

void Battleship::player::modify_boards(player& opp_player, int r, int c) {
  int ships_left = 0;
  for (const auto& ships : config::return_ships()) {
    if (opp_player.set_board[r][c] == ships.first) { // if hits
      fire_board[r][c] = 'X';
      opp_player.set_board[r][c] = 'X';

      print_both_boards(name);

      std::cout << name << " hit " <<
                opp_player.name << "'s " << ships.first << "!" << std::endl;

      for (const auto& rows: opp_player.set_board) { // detecting if there's any leftover ship with the same name
        for (const auto& each : rows) {
          if (each == ships.first) {
            ++ships_left;
          }
        }
      }
      if (ships_left == 0) {
        std::cout << name << " destroyed " <<
                  opp_player.name << "'s " << ships.first << "!" << std::endl;
      }
      std::cout << std::endl;
      last_hit_coord = {r,c};
      hit_status = true;
      return;
    }
  }
  hit_status = false;
  fire_board[r][c] = 'O';
  opp_player.set_board[r][c] = 'O';
  print_both_boards(name);
  std::cout << "Missed." << std::endl << std::endl;
}

void Battleship::human::ask_fire_coord(int& r, int& c) {
  std::string prompt = name + ", where would you like to fire?\n"
                              "Enter your attack coordinate in the form row col: ";
  do {
    print_both_boards(name);
    Battleship::human::get_two_ints(prompt, r, c);
  } while (!check_fire_valid(r, c) || fire_board[r][c] == 'X' || fire_board[r][c] == 'O');
}

bool Battleship::player::check_fire_valid(const int& r, const int& c) {
  return !(r < 0 || c < 0 || r >= config::return_rows() || c >= config::return_col());
}

void Battleship::player::print_both_boards(const std::string& player_name) const {
  std::cout << player_name << "'s Firing Board" << std::endl;
  print_fire_board(); // print fire board
  std::cout << std::endl << std::endl; // two lines
  std::cout << player_name << "'s Placement Board" << std::endl;
  print_og_board(); // print placement board
}
