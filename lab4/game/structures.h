#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

enum step_type_t {
  MOVE,
  ATTACK,
  UNKNOWN
};

struct step_t {
  int from_x, from_y, to_x, to_y;
  step_type_t type;

  step_t(int from_x, int from_y, int to_x, int to_y) :
      from_x{from_x},
      from_y{from_y},
      to_x{to_x},
      to_y{to_y},
      type{UNKNOWN} {}

  void set_type(step_type_t new_type) {
    type = new_type;
  }
};

enum side_t {
  WHITE,
  BLACK
};

enum status_t {
  PLAIN,
  QUEEN,
  DEAD
};

struct checker_t {
public:
  side_t side;
  status_t status;
  int x;
  int y;

  checker_t(side_t side = WHITE, int x = 0, int y = 0) :
      side{side},
      status(PLAIN),
      x{x},
      y{y} {}
};

struct field_t {
private:
  checker_t checkers[24];

public:
  field_t() :
      checkers() {
    for (int i = 0; i < 12; ++i) {
      checker_t new_checker(BLACK, (i % 4) * 2 - (i / 4) % 2 + 2, i / 4 + 1);
      checkers[i] = new_checker;
    }
    for (int i = 0; i < 12; ++i) {
      checker_t new_checker(WHITE, 8 - ((i % 4) * 2 - (i / 4) % 2 + 1), 8 - (i / 4));
      checkers[i + 12] = new_checker;
    }
  }

  void print(side_t side = WHITE) const {
    // prints row number at the beginning of each row (needs because of reversing field depending on side)
    std::cout << ' ' << ' ';
    for (int k = 1; k <= 8; ++k) {
      if (side == WHITE) {
        std::cout << k << ' ';
      } else {
        std::cout << 9 - k;
      }
    }
    std::cout << std::endl;

    for (int i = 1; i <= 8; ++i) {
      // prints row number at the beginning of each row (needs because of reversing field depending on side)
      if (side == WHITE) {
        std::cout << i;
      } else {
        std::cout << 9 - i;
      }
      std::cout << ' ';

      for (int j = 1; j <= 8; ++j) {
        try {
          checker_t tmp_checker;
          if (side == WHITE) {
            tmp_checker = find_checker(j, i);
          } else {
            tmp_checker = find_checker(9 - j, 9 - i);
          }

          if (tmp_checker.side == WHITE) {
            std::cout << 'w';
          } else {
            std::cout << 'b';
          }
        } catch (std::invalid_argument &e) {
          std::cout << '.';
        }
        std::cout << ' ';
      }
      std::cout << std::endl;
    }
  }

  std::vector<step_t> find_possible_steps(const side_t &side) const {
    int delta_y = 1;
    std::vector<step_t> result;
    if (side == BLACK) {
      delta_y = -1;
    }
    for (const checker_t &p : checkers) {
      try {
        checker_t neighbour = find_checker(p.x, p.y);
        if (neighbour.side != side) {

        }
      } catch (std::invalid_argument &e) {

      }
    }
  }

  bool is_correct_step_general(const step_t &step) const {
    int delta_x = step.to_x - step.from_x;
    int delta_y = step.to_y - step.from_y;

    // check that all coordinates are inside of a field
    if (step.from_x < 1 || step.from_x > 8 ||
        step.from_y < 1 || step.from_y > 8 ||
        step.to_x < 1 || step.to_x > 8 ||
        step.to_y < 1 || step.to_y > 8) {
      std::cout << "Some coordinates are outside of the field" << std::endl;
      return false;
    }

    // check that move is diagonal
    if (abs(delta_x) != abs(delta_y)) {
      std::cout << "Step is not diagonal" << std::endl;
      return false;
    }
    return true;
  }


  checker_t &find_checker(int x, int y) {
    for (checker_t &p : checkers) {
      if (p.status != DEAD && p.x == x && p.y == y) {
        return p;
      }
    }
    throw std::invalid_argument("Inner exception when checker is not found");
  }

  const checker_t &find_checker(int x, int y) const {
    for (const checker_t &p : checkers) {
      if (p.status != DEAD && p.x == x && p.y == y) {
        return p;
      }
    }
    throw std::invalid_argument("Inner exception when checker is not found");
  }
};