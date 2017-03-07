#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

enum Score {
    BAD = -8,
    DEFAULT = 0,
    GOOD = 3,
    GREAT = 8
};

class Move {
   
public:
    int x, y, score;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
        this->score = DEFAULT;
    }

    Move(const Move &other) {
        this->x = other.x;
        this->y = other.y;
        this->score = other.score;
    }

    ~Move() {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setScore(int score) { this->score = score; }
    
    bool operator<(const Move &other) const {
        return score < other.score;
    }
};

#endif
