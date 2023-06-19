//
// Created by 葉宥辰 on 2023/6/19.
//

#include "alphabeta.hpp"
#include <cstdlib>

#include "../state/state.hpp"

#define INF 10000000

Move better_move;
Move Alphabeta::get_move(State *state, int depth){
    alphabeta(state, 0, state->player == 0, depth, -INF, INF);
    return better_move;
}

std::pair<int, int> alphabeta(State *state, int step, int isWhite, int maxDepth, int alpha, int beta) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    if (state->game_state != NONE || step == maxDepth) {
        int t = state->evaluate() * (isWhite ? 1 : -1);
        return std::make_pair(t, t);
    }

    if ((step&1) == 0) { // max
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            std::pair<int, int> t = alphabeta(next_state, step + 1, isWhite, maxDepth, alpha, beta);
            if (alpha < t.second) {
                if (step == 0)
                    better_move = action;
                alpha = t.second;
            }
            if (alpha >= beta) {
                return std::make_pair(alpha, beta);
            }
        }
    }
    else {
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            std::pair<int, int> t = alphabeta(next_state, step + 1, isWhite, maxDepth, alpha, beta);
            if (beta > t.first) {
                beta = t.first;
            }
            if (alpha >= beta) {
                return std::make_pair(alpha, beta);
            }
        }
    }
    return std::make_pair(alpha, beta);
}