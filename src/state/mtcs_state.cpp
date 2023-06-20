//
// Created by 葉宥辰 on 2023/6/19.
//

#include "mtcs_state.hpp"
#include <cstdlib>
#include "../state/state.hpp"
#include <random>

Move MTCS_State::get_random_action(State *state) {
    if (!state->legal_actions.size())
        state->get_legal_actions();
    int idx = rand() % state->legal_actions.size();
    return state->legal_actions[idx];
}

int MTCS_State::get_best_child() {
    // UCT
}