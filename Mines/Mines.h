#pragma once

#include "MinesImpl.h"

class Mines {
public:
    Mines(const int row, const int col, const char**& valArray,
          const bool**& revealArray)
            : impl(row, col, valArray, revealArray) {}

    void reInit() { impl.reInit(); }

    ~Mines() = default;

    void initialize(const int initialX, const int initialY,
                    const int mineNum) const {
        impl.initialize(initialX, initialY, mineNum);
    }

    StepResults step(const int x, const int y) { return impl.step(x, y); }

    int getRevNum() const { return impl.getRevNum(); }

    Mines& operator=(const Mines& other) {
        if (this != &other) {
            // Delegate the size checking to MinesImpl
            if (impl.canAssign(other.impl)) {
                impl = other.impl; // Sizes are the same, perform the copy
            } else {
                // Optionally, handle the size mismatch in any way that suits your application
                throw std::invalid_argument("Cannot assign Mines with different dimensions.");
            }
        }
        return *this;
    }


private:
    MinesImpl impl;
};
