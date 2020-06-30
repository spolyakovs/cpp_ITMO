#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) :
  fld() {
  fld.print();
  players.push_back(first);
  players.push_back(second);
}

bool game_t::is_correct_step(int from_x, int from_y, int to_x, int to_y) {
  step_t step = step_t{from_x, from_y, to_x, to_y};
  int delta_x = step.to_x - step.from_x;

  if (!fld.is_correct_step_general(step)) {
    return false;
  }

  switch (abs(delta_x)) {
    case 0:
      std::cout << "Trying stay at the same place" << std::endl;
      return false;
    case 1:
      step.set_type(MOVE);
      return is_correct_step_move(step);
    case 2:
      step.set_type(ATTACK);
      return is_correct_step_attack(step);
    default:
      //return is_correct_step_queen();
      std::cout << "Trying to move too far" << std::endl;
      return false;
  }
}


bool game_t::is_correct_step_move(const step_t &step) {
  std::cout << "move" << std::endl;
  
  int delta_y = step.to_y - step.from_y;

  try {
    checker_t p = fld.find_checker(step.from_x, step.from_y);

    if (side != p.side) {
      std::cout << "Trying to move enemy checker" << std::endl;
      return false;
    }

    //check that checkers move in right direction
    if (delta_y <= 0 && side == BLACK && p.status != QUEEN ||
        delta_y >= 0 && side == WHITE && p.status != QUEEN) {
      std::cout << "Step in wrong direction (y)" << std::endl;
      return false;
    }

    // check that there is no checker where move to
    try {
      fld.find_checker(step.to_x, step.to_y);
      std::cout << "Trying to step on another checker" << std::endl;
      return false;
    } catch (std::invalid_argument &e) {
      return true;
    }

  } catch (std::invalid_argument &e) {
    std::cout << "There is no checker in that position" << std::endl;
    return false;
  }
}
bool game_t::is_correct_step_attack(const step_t &step) {
  std::cout << "attack" << std::endl;
  int delta_y = step.to_y - step.from_y;

  try {
    checker_t p = fld.find_checker(step.from_x, step.from_y);

    if (side != p.side) {
      std::cout << "Trying to move enemy checker" << std::endl;
      return false;
    };

    //check that checkers move in right direction
    if (delta_y <= 0 && side == BLACK && p.status != QUEEN ||
        delta_y >= 0 && side == WHITE && p.status != QUEEN) {
      std::cout << "Step in wrong direction (y)" << std::endl;
      return false;
    }

    // check that there is no checker where move to
    try {
      fld.find_checker(step.to_x, step.to_y);
    } catch (std::invalid_argument &e) {
      try {
        checker_t target = fld.find_checker((p.x + step.to_x) / 2, (p.y + step.to_y) / 2);
        return (side != target.side);
      } catch (std::invalid_argument &e) {
        std::cout << "Trying to attack friendly checker" << std::endl;
        return false;
      }
    }
    std::cout << "Trying to step on another checker" << std::endl;
    return false;

  } catch (std::invalid_argument &e) {
    std::cout << "There is no checker in that position" << std::endl;
    return false;
  }
}

//bool game_t::apply_step(const step_t &step, size_t player_num) {
//  char &cell = fld.fld[step.x - 1][step.y - 1];
//  if (cell != '.') {
//    return false;
//  }
//
//  if (player_num == 0) {
//    cell = '#';
//  } else {
//    cell = '0';
//  }
//  return true;
//}
//
//bool game_t::is_win_line(int x, int y, int dx, int dy) const {
//  char c = field.fld[x][y];
//  if (c == '.') {
//    return false;
//  }
//  for (int i = 0; i < 3; ++i) {
//    if (c != field.fld[x + i * dx][y + i * dy]) {
//      return false;
//    }
//  }
//  return true;
//}
//
//game_t::game_outcome_t game_t::is_win() const {
//  for (int i = 0; i < 3; ++i) {
//    if (is_win_line(0, i, 1, 0) || is_win_line(i, 0, 0, 1)) {
//      return WIN;
//    }
//  }
//  if (is_win_line(0, 0, 1, 1) || is_win_line(0, 2, 1, -1)) {
//    return WIN;
//  }
//  for (auto line : field.fld) {
//    for (int j = 0; j < 3; ++j) {
//      if (line[j] == '.') {
//        return IN_PROGRESS;
//      }
//    }
//  }
//  return TIE;
//}
//
//void game_t::play() {
//  size_t counter = 1;
//  while (is_win() == IN_PROGRESS) {
//    counter = (counter + 1) % 2 ;
//    bool is_correct = false;
//    while (!is_correct) {
//      step_t step = players[counter]->make_step(field);
//      is_correct = apply_step(step, counter);
//      if (!is_correct) {
//        players[counter]->on_incorrect_step(step);
//      }
//    }
//  }
//
//  if (is_win() == TIE) {
//    for (const auto &p : players) {
//      p->on_tie();
//    }
//    return;
//  }
//
//  for (size_t i = 0; i < players.size(); ++i) {
//    if (i == counter) {
//      players[i]->on_win();
//    } else {
//      players[i]->on_lose();
//    }
//  }
//}
