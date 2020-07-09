#include "computer_min_y.h"

#include <cassert>
#include <iostream>
#include <vector>

computer_min_y_t::computer_min_y_t(std::string name) :
  name(std::move(name)) {}

step_t computer_min_y_t::make_step(const field_t &fld, side_t side) {
  std::vector<step_t> possible_steps = fld.find_possible_steps(side);

  assert(!possible_steps.empty());
  step_t elem = possible_steps[0];
  int min_y = elem.to_y;
  for (int i = 1; i < possible_steps.size(); ++i) {
    if (possible_steps[i].to_y < min_y) {
      min_y = possible_steps[i].to_y;
      elem = possible_steps[i];
    }
  }
  return elem;
}

void computer_min_y_t::print_stat() const {
  std::cout << "Random model [" << name << "]: " << std::endl;
  computer_interface_t::print_stat();
}
