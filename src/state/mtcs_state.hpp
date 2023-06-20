//
// Created by 葉宥辰 on 2023/6/19.
//

#ifndef I2P3_MINICHESS_MTCS_STATE_HPP
#define I2P3_MINICHESS_MTCS_STATE_HPP

#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include "../config.hpp"
#include "state.hpp"

class MTCS_State : public State {
public:
    std::vector<int> children;
    void simulate();
    void expand();
    void backpropagate(int reward);
    int get_best_child();
    int get_random_child();
    Move get_random_action(State *state);
};


#endif //I2P3_MINICHESS_MTCS_STATE_HPP
