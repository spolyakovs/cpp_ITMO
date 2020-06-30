#include "human.h"

void human_strategy_t::on_win() {
  std::cout << "You win!" << std::endl;
}
void human_strategy_t::on_lose() {
  std::cout << "You lose!" << std::endl;
}
void human_strategy_t::on_tie() {
  std::cout << "Tie!" << std::endl;
}

step_t human_strategy_t::make_step(const field_t &fld) {
  std::cout << "Field:" << std::endl;
  fld.print();
  std::cout << "Type coordinates (from_x, from_y, to_x, to_y): " << std::endl;
  int from_x, from_y, to_x, to_y;
  std::cin >> from_x >> from_y >> to_x >> to_y;
  return {from_x, from_y, to_x, to_y};
}

void human_strategy_t::on_incorrect_step(const step_t &step) const {
  std::cout << "Incorrect step:" << std::endl;
  std::cout << "  from: [" << step.from_x << ", " << step.from_y << "];" << std::endl;
  std::cout << "  to: [" << step.to_x << ", " << step.to_y << "];" << std::endl;
}
