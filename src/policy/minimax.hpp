//
// Created by 葉宥辰 on 2023/6/19.
//

#pragma once
#include "../state/state.hpp"

int minimax(State *state, int step, int isWhite, int maxDepth);

/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class Minimax {
public:
    static Move get_move(State *state, int depth);
};