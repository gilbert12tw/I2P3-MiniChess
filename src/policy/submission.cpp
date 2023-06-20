//
// Created by 葉宥辰 on 2023/6/19.
//

#include "alphabeta.hpp"
#include <cstdlib>

#include "../state/state.hpp"

#define INF 10000000

Move better_move;

const int material_table[7] = {0, 2, 6, 7, 8, 20, 100};

int getDrawType(State game) {
    int piece;
    int white_material = 0, black_material = 0;
    for(size_t i=0; i<BOARD_H; i+=1){
        for(size_t j=0; j<BOARD_W; j+=1){
            if((piece=game.board.board[0][i][j])){
                white_material += material_table[piece];
            }
            if((piece=game.board.board[1][i][j])){
                black_material += material_table[piece];
            }
        }
    }
    if(white_material<black_material){
        return -1000000;
    }else if(white_material>black_material){
        return 1000000;
    }
    return 0;
}

Move Alphabeta::get_move(State *state, int depth, int moveCount) {
    alphabeta(state, 0, state->player == 0, depth, moveCount, -INF, INF);
    return better_move;
}

std::pair<int, int> alphabeta(State *state, int step, int isWhite, int maxDepth, int moveCount, int alpha, int beta) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    if (moveCount + step == 50) {
        int t = getDrawType(*state) * (isWhite ? 1 : -1);
        return std::make_pair(t, t);
    }

    if (state->game_state != NONE || step == maxDepth) {
        int t = state->evaluate() * (isWhite ? 1 : -1);
        return std::make_pair(t, t);
    }

    if ((step&1) == 0) { // max
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            std::pair<int, int> t = alphabeta(next_state, step + 1, isWhite, maxDepth, moveCount, alpha, beta);
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
            std::pair<int, int> t = alphabeta(next_state, step + 1, isWhite, maxDepth, moveCount, alpha, beta);
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