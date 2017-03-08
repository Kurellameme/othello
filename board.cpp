#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) const {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) const {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

/*
 * Returns true if a square is in a corner of the board.
 */
bool isCorner(int x, int y) {
    return ((x == 0 && y == 0) ||
            (x == 7 && y == 0) ||
            (x == 0 && y == 7) ||
            (x == 7 && y == 7));
}

/* 
 * Returns true if a square is on the edge of the board, but is NOT a corner
 * or directly adjacent to a corner. So, on an 8x8 board, there would be only
 * 4 squares on each side that would be classified as edges.
 */
bool isEdge(int x, int y) {
    return ((x == 0 && y == 2) ||
            (x == 0 && y == 3) ||
            (x == 0 && y == 4) ||
            (x == 0 && y == 5) ||
            (x == 7 && y == 2) ||
            (x == 7 && y == 3) ||
            (x == 7 && y == 4) ||
            (x == 7 && y == 5) ||
            (x == 2 && y == 0) ||
            (x == 3 && y == 0) ||
            (x == 4 && y == 0) ||
            (x == 5 && y == 0) ||
            (x == 2 && y == 7) ||
            (x == 3 && y == 7) ||
            (x == 4 && y == 7) ||
            (x == 5 && y == 7));
}

/*
 * Returns true if a move is next to a corner square on the board.
 */
bool isNextToCorner(int x, int y) {
    return ((x == 1 && y == 0) ||
            (x == 0 && y == 1) ||
            (x == 1 && y == 1) ||
            (x == 6 && y == 0) ||
            (x == 6 && y == 1) ||
            (x == 7 && y == 1) ||
            (x == 0 && y == 6) ||
            (x == 1 && y == 6) ||
            (x == 1 && y == 7) ||
            (x == 6 && y == 7) ||
            (x == 6 && y == 6) ||
            (x == 7 && y == 6));
}

int Board::score(Side side) const {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (occupied(i, j)) { 
                if (get(side, i, j)) {
                    if (isCorner(i, j)) {
                        score += GREAT;
                    }
                    else if (isEdge(i, j)) {
                        score += GOOD;
                    }
                    else if (isNextToCorner(i, j)) {
                        score--;
                    }
                    else {
                        score++;
                    }
                }
                else {
                    if (isCorner(i, j)) {
                        score -= GREAT;
                    }
                    else if (isEdge(i, j)) {
                        score -= GOOD;
                    }
                    else if (isNextToCorner(i, j)) {
                        score++;
                    }
                    else {
                        score--;
                    }
                }
            }
        }
    }
    return score;
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return (possibleMoves(BLACK).empty() && possibleMoves(WHITE).empty());
}

/*
 * Returns a vector of all possible moves.
 * Returns an empty vector if no moves are possible.
 */
//TODO set
std::vector<Move> Board::possibleMoves(Side side) {
    std::vector<Move> possible_moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (occupied(i, j)) {
                if (i != 0) {
                    Move move_left(i-1, j);
                    if (checkMove(&move_left, side)) {
                        possible_moves.push_back(move_left);
                    }
                }
                if (i != 7) {
                    Move move_right(i+1, j); 
                    if (checkMove(&move_right, side)) {
                        possible_moves.push_back(move_right);
                    }
                }
                if (j != 0) {
                    Move move_up(i, j-1); 
                    if (checkMove(&move_up, side)) {
                        possible_moves.push_back(move_up);
                    }
                }
                if (j != 7) {
                    Move move_down(i, j+1);
                    if (checkMove(&move_down, side)) {
                        possible_moves.push_back(move_down);
                    }
                }
            }
        }
    }
    return possible_moves;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return possibleMoves(side).empty();

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}
