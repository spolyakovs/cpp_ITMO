#pragma once

#include "../game/structures.h"

class strategy_interface_t {
public:
  virtual step_t make_step(const field_t &fld, side_t side) = 0;
  virtual void on_incorrect_step(const step_t &step) const = 0;

  virtual void on_lose() = 0;
  virtual void on_win() = 0;
};
