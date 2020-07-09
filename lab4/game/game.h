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
private:
  enum game_outcome_t {
    WIN,
    IN_PROGRESS
  };
  player_t current_player();

  game_outcome_t is_win();
  bool apply_step(step_t &step);
  void change_sides();

  side_t side;
  field_t fld;
  std::pair<player_t, player_t> players;
};

