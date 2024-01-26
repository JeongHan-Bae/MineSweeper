// MinesImpl.h

#pragma once

#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <vector>

enum struct StepResults { LOST, REVEALED, CONTINUE };

class MinesImpl {
public:
    MinesImpl(int row, int col, const char **& charArray, const bool**& boolArray);

    void reInit();

    ~MinesImpl();

    void initialize(int initialX, int initialY, int mineNum) const;

    StepResults step(int x, int y);

    int getRevNum() const;

    MinesImpl& operator=(const MinesImpl& other);

    bool canAssign(const MinesImpl& other) const {
        return (row == other.row && col == other.col);
    }


private:
    const int row, col;
    int revNum;
    const int UsageCol;
    char*const * valMap;
    bool*const * revealMap;
    std::unordered_set<int> revealedSet;

    void Reveal(int Pos);
};
