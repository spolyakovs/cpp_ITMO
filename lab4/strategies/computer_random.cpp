#include "computer_random.h"

#include <cassert>
#include <iostream>
#include <vector>


computer_strategy_t::computer_strategy_t(std::string name) :
  name(std::move(name)) {}

//std::pair<int, int> computer_strategy_t::choose_moving_checker(const field_t fld) {
//
//}
//
//step_t computer_strategy_t::make_step(const field_t &fld) {
//  std::vector<std::pair<int, int>> empty_coordinates;
//
//  assert(!empty_coordinates.empty());
//  std::random_shuffle(empty_coordinates.begin(), empty_coordinates.end());
//  auto elem = empty_coordinates.back();
//  return {elem.first + 1, elem.second + 1};
//}

void computer_strategy_t::print_stat() const {
  std::cout << "Random model [" << name << "]: " << std::endl;
  computer_interface_t::print_stat();
}
