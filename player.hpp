#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <algorithm>
#include "common.hpp"
#include "board.hpp"


#define BOARDSIZE 8

using namespace std;

bool isCorner(int move_x, int move_y);
bool isNextToCorner(int move_x, int move_y);
Move getCornerFromEdge(int move_x, int move_y);
bool isEdge(int move_x, int move_y);

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    void moveScore(Move &move);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board board;
    Side side;
};

#endif
