#pragma once

#include <string>

#include "../game/structures.h"
#include "computer_interface.h"

class computer_min_y_t : public computer_interface_t {
public:
  explicit computer_min_y_t(std::string name);

  step_t make_step(const field_t &field, side_t side) override;

  void print_stat() const override;

private:
  std::string name;
};
