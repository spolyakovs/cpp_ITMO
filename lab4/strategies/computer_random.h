#pragma once

#include <string>

#include "../game/structures.h"
#include "computer_interface.h"

class computer_strategy_t : public computer_interface_t {
public:
  explicit computer_strategy_t(std::string name);

//  std::pair<int, int> choose_moving_checker(const field_t fld) override;
//  step_t make_step(const field_t &field) override;

  void print_stat() const override;

private:
  std::string name;
};
