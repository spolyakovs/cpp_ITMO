#include "structures.h"

field_t::field_t() :
    checkers(), last_attacker(WHITE, 0, 0, DEAD) {
  for (int i = 0; i < 12; ++i) {
    checker_t new_checker(WHITE, (i % 4) * 2 - (i / 4) % 2 + 2, i / 4 + 1);
    checkers[i] = new_checker;
  }
  for (int i = 0; i < 12; ++i) {
    checker_t new_checker(BLACK, 8 - ((i % 4) * 2 - (i / 4) % 2 + 1), 8 - (i / 4));
    checkers[i + 12] = new_checker;
  }
}

void field_t::print(side_t side) const {
  if (side == WHITE) {
    std::cout << "WHITE" << std::endl;
  } else {
    std::cout << "BLACK" << std::endl;
  }


  for (int i = 1; i <= 8; ++i) {
    // prints row number at the beginning of each row (needs because of reversing field depending on side)
    if (side == WHITE) {
      std::cout << 9 - i;
    } else {
      std::cout << i;
    }
    std::cout << ' ';

    for (int j = 1; j <= 8; ++j) {
      try {
        checker_t tmp_checker;
        if (side == WHITE) {
          tmp_checker = find_checker(j, 9 - i);
        } else {
          tmp_checker = find_checker(9 - j, i);
        }

        if (tmp_checker.side == WHITE) {
          if (tmp_checker.status == QUEEN) {
            std::cout << 'W';
          } else {
            std::cout << 'w';
          }
        } else {
          if (tmp_checker.status == QUEEN) {
            std::cout << 'B';
          } else {
            std::cout << 'b';
          }
        }
      } catch (std::invalid_argument &e) {
        std::cout << '.';
      }
      std::cout << ' ';
    }
    std::cout << std::endl;
  }

  // prints column number at the end (needs because of reversing field depending on side)
  std::cout << ' ' << ' ';
  for (int k = 1; k <= 8; ++k) {
    if (side == WHITE) {
      std::cout << k << ' ';
    } else {
      std::cout << 9 - k << ' ';
    }
  }
  std::cout << std::endl;
}

bool field_t::is_correct_step_general(step_t &step, side_t side, bool need_output) const {
  int delta_x = step.to_x - step.from_x;
  int delta_y = step.to_y - step.from_y;

  // check that all coordinates are inside of a field
  if (step.from_x < 1 || step.from_x > 8 ||
      step.from_y < 1 || step.from_y > 8 ||
      step.to_x < 1 || step.to_x > 8 ||
      step.to_y < 1 || step.to_y > 8) {
    if (need_output) {
      std::cout << "Some coordinates are outside of the field" << std::endl;
    }
    return false;
  }

  // check that move is diagonal
  if (abs(delta_x) != abs(delta_y)) {
    if (need_output) {
      std::cout << "Step is not diagonal" << std::endl;
    }
    return false;
  }

  switch (abs(delta_x)) {
    case 0:
      if (need_output) {
        std::cout << "Trying stay at the same place" << std::endl;
      }
      return false;
    case 1:
      if (is_correct_step_move(step, side, need_output)) {
        step.set_type(MOVE);
        return true;
      }
      return false;
    case 2:
      if (is_correct_step_attack(step, side, need_output)) {
        step.set_type(ATTACK);
        return true;
      }
      return is_correct_step_queen(step, side, need_output);
    default:
      return is_correct_step_queen(step, side, need_output);
  }
}
bool field_t::is_correct_step_move(const step_t &step, side_t side, bool need_output) const {

  int delta_y = step.to_y - step.from_y;

  try {
    checker_t p = find_checker(step.from_x, step.from_y);

    if (side != p.side) {
      if (need_output) {
        std::cout << "Trying to move enemy checker" << std::endl;
      }
      return false;
    }

    //check that checkers move in right direction
    if (delta_y >= 0 && side == BLACK && p.status != QUEEN ||
        delta_y <= 0 && side == WHITE && p.status != QUEEN) {
      if (need_output) {
        std::cout << "Step in wrong direction (y)" << std::endl;
      }
      return false;
    }

    // check that there is no checker where move to
    try {
      find_checker(step.to_x, step.to_y);
      if (need_output) {
        std::cout << "Trying to step on another checker" << std::endl;
      }
      return false;
    } catch (std::invalid_argument &e) {
      return true;
    }

  } catch (std::invalid_argument &e) {
    if (need_output) {
      std::cout << "There is no checker in that position" << std::endl;
    }
    return false;
  }
}
bool field_t::is_correct_step_attack(const step_t &step, side_t side, bool need_output) const {

  try {
    checker_t p = find_checker(step.from_x, step.from_y);

    if (side != p.side) {
      if (need_output) {
        std::cout << "Trying to move enemy checker" << std::endl;
      }
      return false;
    }

    // check that there is no checker where move to
    try {
      find_checker(step.to_x, step.to_y);
      if (need_output) {
        std::cout << "Trying to step on another checker" << std::endl;
      }
      return false;
    } catch (std::invalid_argument &e) {
      try {
        checker_t target = find_checker((p.x + step.to_x) / 2, (p.y + step.to_y) / 2);
        if (side == target.side) {
          if (need_output) {
            std::cout << "Trying to attack friendly checker" << std::endl;
          }
          return false;
        }
        return true;
      } catch (std::invalid_argument &e) {
        if (need_output) {
          std::cout << "Trying to move too far" << std::endl;
        }
        return false;
      }
    }

  } catch (std::invalid_argument &e) {
    if (need_output) {
      std::cout << "There is no checker in that position" << std::endl;
    }
    return false;
  }
}
bool field_t::is_correct_step_queen(step_t &step, side_t side, bool need_output) const {

  int delta_y = step.to_y - step.from_y;
  int delta_x = step.to_x - step.from_x;

  try {
    checker_t p = find_checker(step.from_x, step.from_y);

    if (side != p.side) {
      if (need_output) {
        std::cout << "Trying to move enemy checker" << std::endl;
      }
      return false;
    }

    if (p.status != QUEEN) {
      if (need_output) {
        std::cout << "Not queen can not move like this" << std::endl;
      }
      return false;
    }

    // check that there is no checker where move to
    try {
      find_checker(step.to_x, step.to_y);
      if (need_output) {
        std::cout << "Trying to step on another checker" << std::endl;
      }
      return false;
    } catch (std::invalid_argument &e) {
      int enemies_count = 0;
      for (int i = 1; i < abs(delta_x); ++i) {
        try {
          checker_t tmp_checker = find_checker(
              step.from_x + i * (delta_x) / abs(delta_x),
              step.from_y + i * (delta_y) / abs(delta_y));
          if (side != tmp_checker.side) {
            enemies_count++;
          } else {
            if (need_output) {
              std::cout << "Trying to attack friendly checker" << std::endl;
            }
            return false;
          }
        } catch (std::invalid_argument &e) {}
      }

      if (enemies_count == 0) {
        step.set_type(MOVE);
        return true;
      } else if (enemies_count == 1) {
        step.set_type(ATTACK);
        return true;
      }
      if (need_output) {
        std::cout << "Trying to attack more than one enemy checker" << std::endl;
      }
      return false;
    }

  } catch (std::invalid_argument &e) {
    if (need_output) {
      std::cout << "There is no checker in that position" << std::endl;
    }
    return false;
  }
}

std::vector<step_t> field_t::find_possible_steps(side_t side) const {
  std::vector<step_t> res;
  for (int from_x = 1; from_x < 9; from_x++) {
    for (int from_y = 1; from_y < 9; from_y++) {
      for (int to_x = 1; to_x < 9; to_x++) {
        for (int to_y = 1; to_y < 9; to_y++) {
          step_t tmp_step = step_t{from_x, from_y, to_x, to_y};
          if (is_correct_step_general(tmp_step, side, false)) {
            res.push_back(tmp_step);
          }
        }
      }
    }
  }

  bool is_attack = false;
  for (auto &re : res) {
    if (re.type == ATTACK) {
      is_attack = true;
      break;
    }
  }

  std::vector<step_t> new_res;

  for (auto re : res) {
    checker_t p = find_checker(re.from_x, re.from_y);
    if (re.type == ATTACK && p.x == last_attacker.x && p.y == last_attacker.y) {
      new_res.push_back(re);
    }
  }

  if (last_attacker.status == DEAD) {
    if (is_attack) {
      for (auto it = res.end() - 1; it >= res.begin(); it--) {
        if ((*it).type != ATTACK) {
          res.erase(it);
        }
      }
    }

    return res;
  } else {
    return new_res;
  }
}

size_t field_t::checkers_count(side_t side) {
  size_t count = 0;
  for (const checker_t &checker: checkers) {
    if (checker.side == side && checker.status != DEAD) {
      count++;
    }
  }
  return count;
}

checker_t &field_t::find_checker(int x, int y) {
  for (checker_t &p : checkers) {
    if (p.status != DEAD && p.x == x && p.y == y) {
      return p;
    }
  }
  throw std::invalid_argument("Inner exception when checker is not found");
}
const checker_t &field_t::find_checker(int x, int y) const {
  for (const checker_t &p : checkers) {
    if (p.status != DEAD && p.x == x && p.y == y) {
      return p;
    }
  }
  throw std::invalid_argument("Inner exception when checker is not found");
}