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
    std::cerr << "tryna make a change" << std::endl;
    Move *ret;
    board.doMove(opponentsMove, (side == BLACK) ? WHITE : BLACK);
    if (board.possibleMoves(side).empty()) {
        std::cerr << "setting ret to nullptr." << std::endl;
        ret = nullptr;
    } else {
        std::vector<Move> moveset = board.possibleMoves(side);
        ret = &(moveset[rand() % moveset.size()]);
    }
    std::cerr << "doing move at address " << ret << std::endl;
    std::cerr << "move: " << ret->getX() << " " << ret->getY() << std::endl; 
    board.doMove(ret, side);
    std::cerr << "move done" << std::endl;
    return ret;
}
