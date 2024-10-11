#include "random.h"
#include "human.h"
#include "AI.h"
#include "mode.h"

void Battleship::human_vs_human() {
  std::string name1 = Battleship::human::giving_player_name(1);
  Battleship::human human_player1(name1);
  Battleship::human::game_set_up(human_player1);

  std::string name2 = Battleship::human::giving_player_name(2);
  Battleship::human human_player2(name2);
  Battleship::human::game_set_up(human_player2);

  Battleship::human::fight_til_death(human_player1, human_player2);
}
void Battleship::ai_involved(int& mode) {
  if (mode == 2) {
    Battleship::human_vs_ai();
  } else if (mode == 3) {
    int ai_type = select_ai();
    ai_vs_ai(ai_type);
  } else {
    std::cout << "error mode.cpp #1" << std::endl;
  }
}

void Battleship::human_vs_ai() {
  std::string name1 = Battleship::human::giving_player_name(1); // asking name.
  Battleship::human human_player(name1); // constructor
  Battleship::human::game_set_up(human_player); // human setting up

  int ai_type = select_ai();
  std::string name = "AI 1";
  if (ai_type == 1) {
    Battleship::cheating_AI ai(name, human_player.set_board);
    Battleship::something_vs_something <human, cheating_AI> (human_player, ai);
  } else if (ai_type == 2) {
    Battleship::random_AI ai2(name);
    Battleship::something_vs_something <human, random_AI> (human_player, ai2);
  } else if (ai_type == 3) {
    Battleship::hunt_destroy ai3(name);
    Battleship::something_vs_something <human, hunt_destroy> (human_player, ai3);
  }
}

void Battleship::ai_vs_ai(int first_ai_type) {
  std::string name1 = "AI 1", name2 = "AI 2";
  int second_ai_type;
  if (first_ai_type == 1) {
      Battleship::cheating_AI ai(name1); // needs op board later on
      second_ai_type = Battleship::select_ai();

      if (second_ai_type == 1) {
        Battleship::cheating_AI ai_against1(name2, ai.set_board);
        ai.oppo_placement_board = ai_against1.set_board;
        Battleship::something_vs_something <cheating_AI, cheating_AI> (ai, ai_against1);
      } else if (second_ai_type == 2) {
        Battleship::random_AI ai_against2(name2);
        ai.oppo_placement_board = ai_against2.set_board;
        Battleship::something_vs_something <cheating_AI, random_AI> (ai, ai_against2);
      } else if (second_ai_type == 3) {
        Battleship::hunt_destroy ai_against3(name2);
        ai.oppo_placement_board = ai_against3.set_board;
        Battleship::something_vs_something <cheating_AI, hunt_destroy> (ai, ai_against3);
      } else { exit(64); }

  } else if (first_ai_type == 2) {
      Battleship::random_AI ai2(name1);
      second_ai_type = Battleship::select_ai();

      if (second_ai_type == 1) {
        Battleship::cheating_AI ai_against1(name2, ai2.set_board);
        Battleship::something_vs_something <random_AI, cheating_AI> (ai2, ai_against1);
      } else if (second_ai_type == 2) {
        Battleship::random_AI ai_against2(name2);
        Battleship::something_vs_something <random_AI, random_AI> (ai2, ai_against2);
      } else if (second_ai_type == 3) {
        Battleship::hunt_destroy ai_against3(name2);
        Battleship::something_vs_something <random_AI, hunt_destroy> (ai2, ai_against3);
      } else { exit(79); }

  } else if (first_ai_type == 3) {
      Battleship::hunt_destroy ai3(name1);
      second_ai_type = Battleship::select_ai();

      if (second_ai_type == 1) {
        Battleship::cheating_AI ai_against1(name2, ai3.set_board);
        Battleship::something_vs_something <hunt_destroy, cheating_AI> (ai3, ai_against1);
      } else if (second_ai_type == 2) {
        Battleship::random_AI ai_against2(name2);
        Battleship::something_vs_something <hunt_destroy, random_AI> (ai3, ai_against2);
      } else if (second_ai_type == 3) {
        Battleship::hunt_destroy ai_against3(name2);
        Battleship::something_vs_something <hunt_destroy, hunt_destroy> (ai3, ai_against3);
      } else { exit(97); }

  } else {
    std::cout << "error mode.cpp #2" << std::endl;
  }
}

template<class first_player, class second_player>
void Battleship::something_vs_something(first_player& player1, second_player& player2) {
  int r,c ;
  do {
    player1.ask_fire_coord(r, c); // ask coord, needs overriding
    player1.modify_boards(player2, r, c); //needs overriding

    bool p1_status = player2.check_result(player1.name); // no need to override.
    if (p1_status) { break; }

    player2.ask_fire_coord(r, c); // ask coord
    player2.modify_boards(player1, r, c);

  } while (!player1.check_result(player2.name));
}

int Battleship::select_mode() {
  int mode;
  std::string prompt1 = "What type of game do you want to play?\n"
                        "1. Human vs Human\n"
                        "2. Human vs AI\n"
                        "3. AI vs AI\n"
                        "Your choice: ";
  do {
    mode= get_valid_int(prompt1);
  } while (mode != 1 && mode != 2 && mode != 3);
  return mode;
}

int Battleship::select_ai() {
  int ai_type;
  std::string prompt2 = "What AI do you want?\n"
                        "1. Cheating AI\n"
                        "2. Random AI\n"
                        "3. Hunt Destroy AI\n"
                        "Your choice: ";

  do {
    ai_type = Battleship::get_valid_int(prompt2);
  } while (ai_type != 1 && ai_type != 2 && ai_type != 3);

  return ai_type;
}

int Battleship::get_valid_int(const std::string& prompt) {
  std::string line;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, line); //grabs the entire line
    std::stringstream line2parse(line);
    int num;
    line2parse >> num;
    if (line2parse) { //if I was able to read the number
      std::string what_is_left;
      line2parse >> what_is_left;
      if (not line2parse) { //if there is nothing left we will fail to read it
        return num;
      }
    }
  }
}