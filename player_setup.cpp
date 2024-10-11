#include "random.h"
#include "read_file.h"
#include "player_setup.h"
#include "human.h"

void Battleship::human::game_set_up(human& the_player) {
  std::string prompt;
  int r, c;
  char position;
  for (const auto& the_ships : Battleship::config::return_ships()) {
    the_player.print_og_board();
    do {
      position = the_player.get_position(the_ships.first);
      prompt = the_player.name + ", enter the row and column you want to place "
          + the_ships.first + ", which is " + std::to_string(the_ships.second) + " long, at with a space in between row and col: ";
      get_two_ints(prompt, r, c);
    } while (!the_player.checking_valid_r_c(r, c, the_ships, position));

    the_player.place_ship(the_ships, position, r, c);
  }
  the_player.print_og_board(); // in player class
}

std::string Battleship::human::giving_player_name(int player_num){
  std::string name;
  std::cout << "Player " << player_num << " please enter your name: ";
  std::getline (std::cin, name);
  return name;
}

char Battleship::human::get_position(const char& ship_name) {
  std::string prompt = name + ", do you want to place " + ship_name + " horizontally or vertically?\n"
                                                                             "Enter h for horizontal or v for vertical\n"
                                                                             "Your choice: ";
  std::string position;
  do {
    position = Battleship::human::get_valid_string(prompt);
  } while (position != "H" && position != "h" && position != "V" && position != "v");
  return position[0];
}

std::string Battleship::human::get_valid_string(const std::string& prompt) {
  std::string line;
  while (true) {
    std::cout << prompt;
    getline(std::cin, line); //grabs the entire line
    std::stringstream line2parse(line);
    std::string word;
    line2parse >> word;
    if (line2parse) { //if I was able to read the number
      std::string what_is_left;
      line2parse >> what_is_left;
      if (not line2parse) { //if there is nothing left we will fail to read it
        return word;
      }
    }
  }
}

void Battleship::human::get_two_ints(const std::string& prompt, int& num1, int& num2) {
  std::string line;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, line); //grabs the entire line
    std::stringstream line2parse(line);
    line2parse >> num1 >> num2;
    if (line2parse) { //if I was able to read the number
      std::string what_is_left;
      line2parse >> what_is_left;
      if (not line2parse) { //if there is nothing left we will fail to read it
        return;
      }
    }
  }
}

void Battleship::player::place_ship(std::pair<char, int> ship, char position, int r, int c) {
  if (position == 'V' || position == 'v') {
    for (int i = r; i < r + ship.second; ++i) {
      set_board[i][c] = ship.first;
    }
  } else if (position == 'H' || position == 'h') {
    for (int i = c; i < c + ship.second; ++i) {
      set_board[r][i] = ship.first;
    }
  }
}

bool Battleship::player::checking_valid_r_c(int r, int c, std::pair<char, int> ship, char position) {
  bool status = false;
  if (r < 0 || c < 0 || r >= Battleship::config::return_rows() || c >= Battleship::config::return_col()) {
    return status;
  } else if (position == 'V' || position == 'v') {
    if (r + ship.second <= Battleship::config::return_rows()) {
      for (int i = r; i < r + ship.second; ++i) {
        if (  set_board[i][c] != '*' ) {
          return false;
        } else {
          status = true;
        }
      }
    } else {return false;}
  } else if (position == 'H' || position == 'h') {
    if (c + ship.second <= Battleship::config::return_col()) {
      for (int i = c; i < c + ship.second; ++i) {
        if ( set_board[r][i] != '*') {
          return false;
        } else {
          status = true;
        }
      }
    } else {return false;}
  }
  return status;
}

void Battleship::player::print_og_board() const {
  int i = -1;
  std::cout << "  ";
  for (int j = 0; j < config::return_col(); ++j) {
    std::cout << j << " ";
  }
  std::cout << std::endl;

  for (auto & rows : set_board) {
    ++i;
    std::cout << i << " ";
    for (auto & each : rows) {
      std::cout << each << " ";
    }
    std::cout << std::endl;
  }
}

void Battleship::player::print_fire_board() const {
  int i = -1;
  std::cout << "  ";
  for (int j = 0; j < config::return_col(); ++j) {
    std::cout << j << " ";
  }
  std::cout << std::endl;

  for (auto & rows : fire_board) {
    ++i;
    std::cout << i << " ";
    for (auto & each : rows) {
      std::cout << each << " ";
    }
    std::cout << std::endl;
  }
}

