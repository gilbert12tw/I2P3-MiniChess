#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"

// pawn 1, rook 2, knight 3, bishop 4, queen 5, king 6
//const int chess_weight[7] = {0, 100, 400, 320, 330, 900, 20000};
//const int piece_square_table[8][6][5] = {
//        {{}},
//        {
//            {100, 100, 100, 100, 100},
//            {50, 50, 50, 50, 50},
//            {25, 10, 10, 10, 5},
//            {0, 0,  20, 20, 20},
//            {5, 5, 0, -5, -5},
//            {0, 0, 0, 0, 0}
//            },
//        {
//            {0, 0, 0, 0, 0},
//            {5, 10, 10, 10, 10},
//            {-5, 0, 0, 0, -5},
//            {-5, 0, 0, 0, -5},
//            {-5, 0, 0, 0, -5},
//            {0, 0, 5, 5, 5}
//            },
//        {
//            {-50, -40, -30, -40, -50},
//            {-40, -20, 15, -20, -40},
//            {0, 15, 20, 15, 0},
//            {0, 15, 20, 15, 0},
//            {-40, -20, 15, -20, -40},
//            {-50, -40, -30, -40, -50}
//            },
//        {
//            {-20, -10, -10, 0, 0},
//            {-10, 0, 15, 10, 10},
//            {-10, 0, 20, 15, -10},
//            {-10, 0, 20, 15, -10},
//            {-20, 0, 0, 0, -10},
//            {-20, -10, -10, -10, -20}
//            },
//        {
//            {-20, -10, -10, 0, 0},
//            {-10, 0, 15, 10, 10},
//            {-10, 0, 20, 15, -10},
//            {-10, 0, 20, 15, -10},
//            {-20, 0, 0, 0, -10},
//            {-20, -10, -10, -10, -20}
//            },
//        {
//            {-30, -40, -50, -40, -30},
//            {-30, -40, -50, -40, -30},
//            {-30, -40, -50, -40, -30},
//            {-20, -30, -40, -30, -20},
//            {20, 20, 0, 20, 20},
//            {20, 30, 0, 30, 20}
//            },
//        {
//            {-50, -30, -30, -30, -50},
//            {-30, 0, 0, 0, -30},
//            {-10, 20, 30, 20, -10},
//            {-10, 20, 30, 20, -10},
//            {-30, 0, 0, 0, -30},
//            {-50, -30, -30, -30, -50}
//            }
//};

//const int piece_square_table[8][6][5] = {
//        {{}},
//        {
//                {100, 100, 100, 100, 100},
//                {50, 50, 50, 50, 50},
//                {30, 30, 20, 10, 10},
//                {5, -5, -10, 0, 0},
//                {5, 10, 10, -20, -20},
//                {0, 0, 0, 0, 0}
//        },
//        {
//                {0, 0, 0, 0, 0},
//                {10, 10, 10, 10, 5},
//                {0, 0, 0, 0, -5},
//                {-5, 0, 0, 0,0},
//                {-5, 0, 0, 0, 0},
//                {0, 0, 0, 5, 5}
//        },
//        {
//                {-30, -30, -30, -40, -50},
//                {0, 0, 0, -20, -40},
//                {15, 15, 10, 0, -30},
//                {-30, 5, 10, 15, 15},
//                {-40, -20, 0, 5, 5},
//                {-50, -40, -30, -30, -30}
//        },
//        {
//                {-10, -10, -10, -10, -20},
//                {0, 0, 0, 0, -10},
//                {10, 10, 5, 0, -10},
//                {-10, 10, 10, 10, 10},
//                {-10, 5, 0, 0, 0},
//                {-20, -10, -10, -10, -10}
//        },
//        {
//                {-5, -5, -10, -10, -20},
//                {0, 0, 0, 0, -10},
//                {5, 5,5, 0, -10},
//                {-10, 5, 5, 5, 5},
//                {-10, 0, 5, 0, 0},
//                {-20, -10, -10, -5, -5}
//        },
//        {
//                {-50, -50, -40, -40, -30},
//                {-50, -50, -40, -40, -30},
//                {-50, -50, -40, -40, -30},
//                {-10, -20, -20, -20, -20},
//                {20, 20, 0, 0, 0},
//                {20, 30, 10, 0, 0}
//        },
//        {
//                {-20, -20, -30, -40, -50},
//                {0, 0, -10, -20, -30},
//                {30, 30, 20, -10, -30},
//                {-30, -10, 20, 30, 30},
//                {-30, -30, 0, 0, 0},
//                {-50, -30, -30, -30, -30}
//        }
//};

// pawn 1, rook 2, knight 3, bishop 4, queen 5, king 6
const int chess_weight[7] = {0, 100, 479, 280, 320, 929, 60000};
const int piece_square_table[8][6][5] = {
        {},
        {
            {0,   0,   0,   0,   0},
            {73, 102,  82,  85,  90},
            {44,  40,  31,  44,   7},
            {-22,   9,   5, -11, -10},
            {-31,   8,  -7, -37, -36},
            {0,   0,   0,   0,   0}
            },
        {
            {4,  37,  33,  56,  50},
            { 67,  55,  62,  34,  60},
            {33,  45,  27,  25,  15},
            {-42, -28, -42, -25, -25},
            {-53, -38, -31, -26, -29},
            {-30, -24, -18,   5,  -2}
            },
        {
                {-75, -10, -55, -58, -70},
                {-36, 4, 62, -4, -14},
                {74, 73, 27, 62, -2},
                {-18, 10, 13, 22, 18},
                {-23, -15, 2, 0, 2},
                {-74, -23, -26, -24, -19}
            },
        {
            {-76, -23,-107, -37, -50},
            {-42, -39,  31,   2, -22},
            {41,  52, -10,  28, -14},
            {14,  25,  24,  15,   8},
            {6,   7,   6,  20,  16},
            {-7,   2, -15, -12, -14}
            },
        {
            {-104, 69, 24, 88, 26},
            {-10, 20, 76, 57, 24},
            {60, 72, 63, 43, 2},
            {-30, -6, -13, -11, -16},
            {-36, -18, 0, -19, -15},
            {-39, -30, -31, -13, -31}
            },
        {
            {-99, -99,  60,  83, -62},
            {56,  56,  55,  10,   3},
            {44, -67,  28,  37, -31},
            {-47, -42, -43, -79, -64},
            {-4,   3, -14, -50, -57},
            {17,  30,  -3, -14,   6}
            },
        {
            {-99, -99,  60,  83, -62},
            {56,  56,  55,  10,   3},
            {44, -67,  28,  37, -31},
            {-47, -42, -43, -79, -64},
            {-4,   3, -14, -50, -57},
            {17,  30,  -3, -14,   6}
            }
};

/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(){
    int scorefirst = 0, scoresecond = 0, endgame = 0, cnt[2] = {0, 0}, qcnt[2] = {0, 0};
    if (this->game_state == WIN) {
        if (this->player == 0) {
            scorefirst += 1000000;
        }
        else {
            scorefirst -= 1000000;
        }
    }

    for (int i = 0; i < BOARD_H; i++) {
        for (int j = 0; j < BOARD_W; j++) {
            if (this->board.board[0][i][j] != 0) {
                scorefirst += chess_weight[this->board.board[0][i][j]];
                if (this->board.board[0][i][j] > 1) cnt[0]++;
                if (this->board.board[0][i][j] == 5) {
                    qcnt[0]++;
                }
            }
            if (this->board.board[1][i][j] != 0) {
                scorefirst -= chess_weight[this->board.board[1][i][j]];
                if (this->board.board[1][i][j] > 1) cnt[1]++;
                if (this->board.board[1][i][j] == 5) {
                    qcnt[1]++;
                }
            }
        }
    }

    if ((qcnt[0] == 0 || cnt[0] <= 3) && (qcnt[1] == 0 || cnt[1] <= 3)) {
        endgame = 1;
    }

    for (int i = 0; i < BOARD_H; i++) {
        for (int j = 0; j < BOARD_W; j++) {
            if (this->board.board[0][i][j] != 0) {
                if (endgame && this->board.board[0][i][j] == 6)
                    scoresecond += piece_square_table[this->board.board[0][i][j] + 1][i][j];
                else
                    scoresecond += piece_square_table[this->board.board[0][i][j]][i][j];
            }

            if (this->board.board[1][i][j] != 0) {
                if (endgame && this->board.board[1][i][j] == 6)
                    scoresecond -= piece_square_table[this->board.board[1][i][j] + 1][5-i][4-j];
                else
                    scoresecond -= piece_square_table[this->board.board[1][i][j]][5-i][4-j];
            }
        }
    }
    return scorefirst + scoresecond;
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
inline void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}