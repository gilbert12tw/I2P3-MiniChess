//
// Created by 葉宥辰 on 2023/6/19.
//

#pragma once
#include "../state/state.hpp"
#include <utility>

std::pair<int, int>  alphabeta(State *state, int step, int isWhite, int maxDepth, int alpha, int beta);

/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class Alphabeta {
public:
    static Move get_move(State *state, int depth);
};