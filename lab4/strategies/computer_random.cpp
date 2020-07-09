#include "computer_random.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <random>

computer_random_t::computer_random_t(std::string name) :
  name(std::move(name)) {}

step_t computer_random_t::make_step(const field_t &fld, side_t side) {
  std::vector<step_t> possible_steps = fld.find_possible_steps(side);

  assert(!possible_steps.empty());
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(possible_steps.begin(), possible_steps.end(), g);
  auto elem = possible_steps.back();
  return elem;
}

void computer_random_t::print_stat() const {
  std::cout << "Random model [" << name << "]: " << std::endl;
  computer_interface_t::print_stat();
}
