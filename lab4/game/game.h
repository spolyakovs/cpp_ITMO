#pragma once

#include <memory>
#include <vector>

#include "../strategies/interface.h"
#include "structures.h"

class game_t {
public:
  using player_t = std::shared_ptr<strategy_interface_t>;
  game_t(const player_t &first, const player_t &second);

  void play();

  bool is_correct_step(int from_x, int from_y, int to_x, int to_y);
  bool is_correct_step_move(const step_t &step);
  bool is_correct_step_attack(const step_t &step);

private:
  side_t side = WHITE;
  enum game_outcome_t {
    WIN,
    TIE,
    IN_PROGRESS
  };

  bool is_win_line(int x, int y, int dx, int dy) const;
  game_outcome_t is_win() const;
  bool apply_step(const step_t &step, size_t player_num);
  void change_sides();

  field_t fld;
  std::vector<player_t> players;
};

