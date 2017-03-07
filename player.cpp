#include "player.hpp"
#include <vector>
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->board = Board();
    this->side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Score a move based on our heuristic.
 *
 * move is the move to make
 * board is the board the move will be made on
 * side is the side that would be making the move.
 *
 * returns one of three Score enums defined in common.hpp.
 */
void Player::moveScore(Move &move) { 
    int x = move.getX();
    int y = move.getY();
    if (isCorner(x, y)) {
        move.setScore(GREAT);
    }
    else if (isNextToCorner(x, y)) {
        // figure out which corner we're next to.
        Move corner = getCornerFromEdge(x, y);
        // if we already played a piece in that corner, this move
        // is great for us!
        if (this->board.get(side, corner.getX(), corner.getY())) {
            move.setScore(GREAT);
        }
        // if there's a move made in the corner made by them, they already
        // have the corner, so this move isn't horrible. 
        else if (this->board.get((this->side == BLACK) ? WHITE : BLACK, corner.getX(), corner.getY())) {
            move.setScore(DEFAULT);
        }
        // if there's no move in the corner yet, moving here would be a huge
        // mistake because we might open up the corner for the opponent.
        else {
            move.setScore(BAD);
        }
    }
    else if (isEdge(x, y)) {
        // edges are just good moves in general
        move.setScore(GOOD);
    }
    else {
        // everything else is just default.
        move.setScore(DEFAULT);
    }
}

/*
 * Returns true if a move is in a corner of the board.
 */
bool isCorner(int move_x, int move_y) {
    return ((move_x == 0 && move_y == 0) ||
            (move_x == 7 && move_y == 0) ||
            (move_x == 0 && move_y == 7) ||
            (move_x == 7 && move_y == 7));
}

/*
 * Returns true if a move is next to a corner square on the board.
 */
bool isNextToCorner(int move_x, int move_y) {
    return ((move_x == 1 && move_y == 0) ||
            (move_x == 0 && move_y == 1) ||
            (move_x == 1 && move_y == 1) ||
            (move_x == 6 && move_y == 0) ||
            (move_x == 6 && move_y == 1) ||
            (move_x == 7 && move_y == 1) ||
            (move_x == 0 && move_y == 6) ||
            (move_x == 1 && move_y == 6) ||
            (move_x == 1 && move_y == 7) ||
            (move_x == 6 && move_y == 7) ||
            (move_x == 6 && move_y == 6) ||
            (move_x == 7 && move_y == 6));
}

/*
 * Takes an edge that is next to a corner square on the board and
 * returns a Move holding the corner square that the move is next to.
 *
 * NOTE: ONLY PASS SQUARES THAT ARE NEXT TO A CORNER SQUARE TO THIS METHOD.
 * IF NOT, YOU WILL GET Move(7, 7) RETURNED WHICH WILL ALMOST CERTAINLY BREAK
 * THINGS.
 */
Move getCornerFromEdge(int move_x, int move_y) {
    if ((move_x == 1 && move_y == 0) ||
        (move_x == 0 && move_y == 1) ||
        (move_x == 1 && move_y == 1)) {
        return Move(0, 0);
    }
    else if ((move_x == 6 && move_y == 0) ||
             (move_x == 6 && move_y == 1) ||
             (move_x == 7 && move_y == 1)) {
        return Move(7, 0);
    }
    else if ((move_x == 0 && move_y == 6) ||
             (move_x == 1 && move_y == 6) ||
             (move_x == 1 && move_y == 7)) {
        return Move(0, 7);
    }
    else {
        return Move(7, 7);
    }
}


/* 
 * Returns true if a move is on the edge of the board, but is NOT a corner
 * or directly adjacent to a corner. So, on an 8x8 board, there would be only
 * 4 squares on each side that would be classified as edges.
 */
bool isEdge(int move_x, int move_y) {
    return ((move_x == 0 && move_y == 2) ||
            (move_x == 0 && move_y == 3) ||
            (move_x == 0 && move_y == 4) ||
            (move_x == 0 && move_y == 5) ||
            (move_x == 7 && move_y == 2) ||
            (move_x == 7 && move_y == 3) ||
            (move_x == 7 && move_y == 4) ||
            (move_x == 7 && move_y == 5) ||
            (move_x == 2 && move_y == 0) ||
            (move_x == 3 && move_y == 0) ||
            (move_x == 4 && move_y == 0) ||
            (move_x == 5 && move_y == 0) ||
            (move_x == 2 && move_y == 7) ||
            (move_x == 3 && move_y == 7) ||
            (move_x == 4 && move_y == 7) ||
            (move_x == 5 && move_y == 7));
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    // process opponent's move
    board.doMove(opponentsMove, (side == BLACK) ? WHITE : BLACK);

    // decide what move to use from our possible moves
    std::vector<Move> moveset = board.possibleMoves(side);
    Move *max_scoring_move;

    // if there aren't any moves to make, use nullptr as best move to pass
    if (moveset.empty()) {
        max_scoring_move = nullptr;
    } else {
        // we loop through all the moves and compute their scores, then use 
        // the highest scoring move.
        for (unsigned int i = 0; i < moveset.size(); i++) {
            moveScore(moveset[i]);
        }
        max_scoring_move = new Move(*std::max_element(moveset.begin(), moveset.end()));
    }

    board.doMove(max_scoring_move, side);
    return max_scoring_move;
}
