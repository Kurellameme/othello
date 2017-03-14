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
/*
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
*/


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
    // process opponent's move
    board.doMove(opponentsMove, (side == BLACK) ? WHITE : BLACK);

    // look at all our possible moves
    std::vector<Move> moveset = board.possibleMoves(side);
    Move *ret;
    int minmax;

    // if there aren't any moves to make, use nullptr
    if (moveset.empty()) {
        ret = nullptr;
    } else {
        // we loop through all the moves and make copies of boards to do them on.
        int total_score;
        for (unsigned int i = 0; i < moveset.size(); i++) {
            std::vector<int> total_scores;
            // moveScore(moveset[i]);
            Board *one_deep = board.copy();
            one_deep->doMove(&moveset[i], side);
            // then, for each board we made a move on, do all moves on that
            // board for the other side.
            std::vector<Move> new_moveset = one_deep->possibleMoves((side == BLACK) ? WHITE : BLACK);
            if (new_moveset.empty()) {
                // they're gonna pass, so we know the total score is just
                // the score from our board
                total_score = one_deep->score(side);
                total_scores.push_back(total_score);
            }
            else {
                for (unsigned int j = 0; j < new_moveset.size(); j++) {
                    // moveScore(new_moveset[j]);
                    Board *two_deep = one_deep->copy();
                    two_deep->doMove(&new_moveset[j], (side == BLACK) ? WHITE : BLACK);
                    total_score = two_deep->score(side);
                    total_scores.push_back(total_score);
                    delete two_deep;
                }
            }
            // once that inner for loop is over, we have all the total scores
            // that could result from us playing the move we are currently 
            // considering. so, we can figure out what the worst case is
            // by taking the min.
            int current_min = *std::min_element(total_scores.begin(), total_scores.end());
            if (i == 0) {
                minmax = current_min;
                ret = new Move(moveset[i]);
            }
            else if (current_min > minmax) {
                minmax = current_min;
                ret = new Move(moveset[i]);
            }
            total_scores.clear();
            delete one_deep;
        }
    }
    board.doMove(ret, side);
    return ret;
}
