#include "human.h"

void human_strategy_t::on_win() {
  std::cout << "You win!" << std::endl;
}
void human_strategy_t::on_lose() {
}

step_t human_strategy_t::make_step(const field_t &fld, side_t side) {
  std::cout << "Field:" << std::endl;
  fld.print(side);
  std::cout << "Type coordinates (from_x from_y to_x to_y): " << std::endl;
  int from_x, from_y, to_x, to_y;
  std::cin >> from_x >> from_y >> to_x >> to_y;
  return {from_x, from_y, to_x, to_y};
}

void human_strategy_t::on_incorrect_step(const step_t &step) const {
  std::cout << "Incorrect step:" << std::endl;
  step.print();
}
