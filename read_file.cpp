#include "read_file.h"
#include "read_cmd.h"
#include "random.h"

int Battleship::config::rows;
int Battleship::config::columns;
int Battleship::config::ship_num;
std::map<char, int> Battleship::config::ships;

Battleship::config::config() {
  char ship_name;
  int ship_config;
  std::ifstream file(Battleship::cmd_storing::file_name);

  if (!file.is_open()) {
    std::cout << "Could not open file"<< std::endl;
    exit(2);
  }

  file >> rows;
  file >> columns;
  file >> ship_num;

  while (!file.eof()) {
    file >> ship_name;
    file >> ship_config;
    ships.insert(std::pair<char,int> (ship_name,ship_config));
  }
  file.close();
}