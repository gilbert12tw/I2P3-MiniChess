//
// Created by 葉宥辰 on 2023/6/19.
//

#include "minimax.hpp"
#include <cstdlib>

#include "../state/state.hpp"

#define INF 10000000

Move best_move;
Move Minimax::get_move(State *state, int depth){
    minimax(state, 0, state->player == 0, depth);
    return best_move;
}

int minimax(State *state, int step, int isWhite, int maxDepth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    if (state->game_state == WIN || step == maxDepth) {
        return state->evaluate() * (isWhite ? 1 : -1);
    }

    if ((step&1) == 0) { // max
        int mx = -INF;
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            int prv_mx = mx;
            mx = std::max(mx, minimax(next_state, step + 1, isWhite, maxDepth));
            if (step == 0 && mx > prv_mx) {
                best_move = action;
            }
        }
        return mx;
    }
    else { // min
        int mn = INF;
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            mn = std::min(mn, minimax(next_state, step + 1, isWhite, maxDepth));
        }
        return mn;
    }
}