cmake_minimum_required(VERSION 3.5.1)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip main.cpp random.h read_cmd.h read_cmd.cpp read_file.cpp read_file.h
                mode.cpp mode.h player_setup.h player_setup.cpp fight_til_death.cpp AI.cpp AI.h)
