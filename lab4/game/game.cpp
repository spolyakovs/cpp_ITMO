#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) :
  fld(), side(WHITE) {
  players.first = first;
  players.second = second;
}

void game_t::change_sides() {
  if (side == WHITE) {
    side = BLACK;
  } else {
    side = WHITE;
  }
}

bool game_t::apply_step(step_t &step) {
  bool is_possible_step = false;

  for (const step_t &possible_step : fld.find_possible_steps(side)) {
    if (step == possible_step) {
      step.type = possible_step.type;
      is_possible_step = true;
      break;
    }
  }
  if (!is_possible_step) {
    return false;
  }

  checker_t &p = fld.find_checker(step.from_x, step.from_y);
  p.move_to(step.to_x, step.to_y);

  // if moved to last row - turn checker into queen
  if (p.status == PLAIN &&
      ((side == WHITE && p.y == 8) ||
      (side == BLACK && p.y == 1))) {
    p.status = QUEEN;
  }

  if (step.type == ATTACK) {
    fld.last_attacker = p;
    int delta_x = step.to_x - step.from_x;
    int delta_y = step.to_y - step.from_y;

    for (int i = 1; i < abs(delta_x); ++i) {
      try {
        checker_t &tmp_checker = fld.find_checker(
            step.from_x + i * (delta_x) / abs(delta_x),
            step.from_y + i * (delta_y) / abs(delta_y));
        tmp_checker.move_to(0,0);
        tmp_checker.status = DEAD;
      } catch (std::invalid_argument &e) {
      }
    }

    if (fld.find_possible_steps(side).empty() && is_win() == IN_PROGRESS) {
      // it does not kill checker in $fld.checkers, but shows that
      fld.last_attacker = checker_t{WHITE, 0, 0, DEAD};
      change_sides();
    }
  } else {
    change_sides();
  }

  return true;
}

game_t::game_outcome_t game_t::is_win() {
  change_sides();
  if (fld.checkers_count(side) == 0 || fld.find_possible_steps(side).empty()) {
    change_sides();
    return WIN;
  }
  change_sides();
  return IN_PROGRESS;
}

game_t::player_t game_t::current_player() {
  if (side == WHITE) {
    return players.first;
  } else {
    return players.second;
  }
}

void game_t::play() {
  while (is_win() == IN_PROGRESS) {
    bool is_correct = false;
    player_t player;
    while (!is_correct) {
      player = current_player();
      step_t step = player->make_step(fld, side);
      is_correct = apply_step(step);
      if (!is_correct) {
        if (fld.is_correct_step_general(step, side, true)) {
          std::cout << "Trying not to attack enemy checker despite that there is an opportunity" << std::endl;
        }
        player->on_incorrect_step(step);
      }
    }
  }

  current_player()->on_win();
  change_sides();
  current_player()->on_lose();
}
