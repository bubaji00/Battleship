#ifndef BATTLESHIP__READ_FILE_H_
#define BATTLESHIP__READ_FILE_H_

#include "random.h"

namespace Battleship {

class config {

 public:
  explicit config();

  static int return_rows() { return rows; }
  static int return_col() { return columns; }
  static std::map<char, int> return_ships() { return ships; }

 private:
  static int rows;
  static int columns;
  static int ship_num;
  static std::map<char, int> ships;
  };
}

#endif //BATTLESHIP__READ_FILE_H_