// MinesImpl.cpp

#include "MinesImpl.h"

MinesImpl::MinesImpl(const int row, const int col, const char **& charArray,
                     const bool **& boolArray)
        : row(row), col(col), revNum(0), UsageCol(col + 2), valMap(new char*[row]),
          revealMap(new bool*[row]) {
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("Invalid input.");
    }
          
    // Declare temporary pointers for assigning charArray and boolArray
    char** tempCharArray = new char*[row];
    bool** tempBoolArray = new bool*[row];

    // Allocate memory for array of pointers
    char** tempValMap = new char*[row];
    bool** tempRevealMap = new bool*[row];

    for (int i = 0; i < row; ++i) {
        // Allocate memory for individual arrays
        tempValMap[i] = new char[col];
        tempRevealMap[i] = new bool[col];
        std::fill(tempValMap[i], tempValMap[i] + col, 0);
        std::fill(tempRevealMap[i], tempRevealMap[i] + col, false);
    }

    // Assign temp pointers to const pointers
    valMap = tempValMap;
    revealMap = tempRevealMap;

    // Assign pointers to charArray and boolArray
    for (int i = 0; i < row; ++i) {
        tempCharArray[i] = valMap[i];
        tempBoolArray[i] = revealMap[i];
    }

    charArray = const_cast<const char**>(tempCharArray);
    boolArray = const_cast<const bool**>(tempBoolArray);

    /* Include border cells in the revealedSet to avoid repetitive border
     * checking.*/
    for (int j = -1; j <= col; ++j) {
        revealedSet.insert(-1 * UsageCol + j);
        revealedSet.insert(row * UsageCol + j);
    }
    for (int i = 0; i < row; ++i) {
        revealedSet.insert(i * UsageCol - 1);
        revealedSet.insert(i * UsageCol + col);
    }
}

// Destructor to deallocate memory
MinesImpl::~MinesImpl() {
    for (int i = 0; i < row; ++i) {
        delete[] valMap[i];
        delete[] revealMap[i];
    }
    delete[] valMap;
    delete[] revealMap;
}

void MinesImpl::reInit() {
    for (int i = 0; i < row; ++i) {
        std::fill(valMap[i], valMap[i] + col, 0);
        std::fill(revealMap[i], revealMap[i] + col, false);
    }
    revNum = 0;
    revealedSet.clear();
    for (int j = -1; j <= col; ++j) {
        revealedSet.insert(-1 * UsageCol + j);
        revealedSet.insert(row * UsageCol + j);
    }
    for (int i = 0; i < row; ++i) {
        revealedSet.insert(i * UsageCol - 1);
        revealedSet.insert(i * UsageCol + col);
    }
}

void MinesImpl::initialize(int initialX, int initialY, int mineNum) const {
    // Validate initialX and initialY
    if (initialX < 0 || initialX >= row || initialY < 0 || initialY >= col) {
        std::cerr << "Error: Initial position is out of bounds." << std::endl;
        return;
    }

    // Validate mineNum
    if (mineNum >= row * col) {
        std::cerr << "Error: Number of mines exceeds or equals the total "
                     "number of cells."
                  << std::endl;
        return;
    }

    // Set mines
    std::vector<int> to_rand(row * col);
    std::iota(to_rand.begin(), to_rand.end(), 0);

    auto it = to_rand.begin() + initialX * col + initialY;
    to_rand.erase(it);

    std::shuffle(to_rand.begin(), to_rand.end(),
                 std::mt19937(std::random_device()()));

    for (int i = 0; i < mineNum; ++i) {
        int minePos = to_rand[i];
        int mineRow = minePos / col;
        int mineCol = minePos % col;

        valMap[mineRow][mineCol] = -1;

        // Update surrounding cells
        for (int surrRow = std::max(0, mineRow - 1);
             surrRow <= std::min(row - 1, mineRow + 1); ++surrRow) {
            for (int surrCol = std::max(0, mineCol - 1);
                 surrCol <= std::min(col - 1, mineCol + 1); ++surrCol) {
                if (valMap[surrRow][surrCol] != -1) {
                    valMap[surrRow][surrCol]++;
                }
            }
        }
    }
    to_rand.clear();
}

StepResults MinesImpl::step(int x, int y) {
    // Step on mine
    if (valMap[x][y] == -1) {
        return StepResults::LOST;
    }

    int pos = x * UsageCol + y;
    // Revealed cell or border
    if (revealedSet.count(pos) > 0) {
        return StepResults::REVEALED;
    }

    // Use iterative method to reveal
    Reveal(pos);
    return StepResults::CONTINUE;
}

int MinesImpl::getRevNum() const { return revNum; }

MinesImpl& MinesImpl::operator=(const MinesImpl& other) {
    if (this != &other) {
        // Delegate the size checking to canAssign function
        if (canAssign(other)) {
            // Deallocate existing memory
            for (int i = 0; i < row; ++i) {
                delete[] valMap[i];
                delete[] revealMap[i];
            }
            delete[] valMap;
            delete[] revealMap;

            // Copy member variables
            revNum = other.revNum;

            // Copy pointers to char arrays
            valMap = other.valMap;
            revealMap = other.revealMap;

            // Copy revealed set
            revealedSet = other.revealedSet;
        } else {
            // Optionally, handle the size mismatch in any way that suits your application
            throw std::invalid_argument("Cannot assign MinesImpl with different dimensions.");
        }
    }
    return *this;
}

// Use stack to realize Iterative Loop
void MinesImpl::Reveal(const int Pos) {
    // Use the X * UsageCol + Y as Pos
    std::stack<int> parsingStack;
    parsingStack.emplace(Pos);
    while (!parsingStack.empty()) {
        int pos = parsingStack.top();
        parsingStack.pop();
        if (revealedSet.count(pos) == 0) {
            int x = pos / UsageCol;
            int y = pos % UsageCol;
            revealMap[x][y] = true;
            revNum++;
            revealedSet.insert(pos);
            if (valMap[x][y] == 0) {
                parsingStack.emplace(pos - 1);
                parsingStack.emplace(pos + 1);
                parsingStack.emplace(pos - UsageCol);
                parsingStack.emplace(pos + UsageCol);
            }
        }
    }
}


