#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

enum step_type_t {
  UNKNOWN,
  MOVE,
  ATTACK
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

  void print() const {
    std::cout << "From (" << from_x << ", " << from_y << ") to (" << to_x << ", " << to_y << ')' << std::endl;
  }

  bool operator==(const step_t &other_step) const {
    return (from_x == other_step.from_x &&
        from_y == other_step.from_y &&
        to_x == other_step.to_x &&
        to_y == other_step.to_y);
  }
};

enum side_t {
  WHITE,
  BLACK
};

enum status_t {
  DEAD,
  PLAIN,
  QUEEN
};

struct checker_t {
public:
  side_t side;
  status_t status;
  int x;
  int y;

  checker_t(side_t side = WHITE, int x = 0, int y = 0, status_t status = PLAIN) :
      side{side},
      status{status},
      x{x},
      y{y} {}

  void move_to(int to_x, int to_y) {
    x = to_x;
    y = to_y;
  }
};

struct field_t {
private:
  checker_t checkers[24];

public:
  checker_t last_attacker;

  field_t();

  void print(side_t side = WHITE) const;

  bool is_correct_step_general(step_t &step, side_t side, bool need_output) const;

  bool is_correct_step_move(const step_t &step, side_t side, bool need_output) const;
  bool is_correct_step_attack(const step_t &step, side_t side, bool need_output) const;
  bool is_correct_step_queen(step_t &step, side_t side, bool need_output) const;

  std::vector<step_t> find_possible_steps(side_t side) const;

  size_t checkers_count(side_t side);

  checker_t &find_checker(int x, int y);
  const checker_t &find_checker(int x, int y) const;
};