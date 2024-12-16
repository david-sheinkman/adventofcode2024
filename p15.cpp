#include <iostream>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p15_1() {
    auto data = readFile(DATA_PATH + "p15.txt");
    vector<string> grid;
    string moves;
    bool firstPart = true;
    for (const auto& row : data) {
        if (row.empty()) firstPart = false;
        else {
            if (firstPart) grid.emplace_back(row);
            else moves += row;
        }
    }
    size_t rr = 0;
    size_t rc = 0;
    for (size_t r = 0; r < grid.size(); ++r) {
        for (size_t c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == '@') {
                rr = r;
                rc = c;
            }
        }
    }
    auto horzinalMove = [&](int d) {
        size_t c = rc + d;
        for (; c > 0 && grid[rr][c] != '#'; c += d) {
            if (grid[rr][c] == '.') {
                if (d == -1) for (; c < rc; ++c) grid[rr][c] = grid[rr][c - d];
                else for (; c > rc; --c) grid[rr][c] = grid[rr][c - d];
                grid[rr][rc] = '.';
                rc += d;
                break;
            }
        }
    };
    auto verticalMove = [&](int d) {
        size_t r = rr + d;
        for (; r > 0 && grid[r][rc] != '#'; r += d) {
            if (grid[r][rc] == '.') {
                if (d == -1) for (; r < rr; ++r) grid[r][rc] = grid[r - d][rc];
                else for (; r > rr; --r) grid[r][rc] = grid[r - d][rc];
                grid[rr][rc] = '.';
                rr += d;
                break;
            }
        }
        };
    for (auto m : moves) {
        if (m == '<') horzinalMove(-1);
        else if (m == '>') horzinalMove(1);
        else if (m == '^') verticalMove(-1);
        else if (m == 'v') verticalMove(1);
    }

    int64_t sum = 0;
    for (size_t r = 0; r < grid.size(); ++r) {
        for (size_t c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 'O') sum += 100 * r + c;
        }
    }
    print(sum);
}

void p15_2() {
    auto data = readFile(DATA_PATH + "p15.txt");
    vector<string> grid;
    string moves;
    bool firstPart = true;
    for (const auto& row : data) {
        if (row.empty()) firstPart = false;
        else {
            if (firstPart) grid.emplace_back(row);
            else moves += row;
        }
    }
    size_t rr = 0;
    size_t rc = 0;
    for (size_t r = 0; r < grid.size(); ++r) {
        for (size_t c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == '@') {
                rr = r;
                rc = c;
            }
        }
    }
    rc *= 2;
    vector<pair<size_t, size_t>> boxes;
    vector<string> newGrid;
    for (size_t r = 0; r < grid.size(); ++r) {
        auto& newRow = newGrid.emplace_back();
        for (size_t c = 0; c < grid[0].size(); ++c) {
            char e = grid[r][c];
            if (e == '#') newRow += "##";
            else if (e == 'O') {
                //newRow += "[]";
                newRow += "..";
                boxes.emplace_back(2 * c, r);
            }
            else if (e == '.') newRow += "..";
            else if (e == '@') newRow += "..";
        }
    }
    grid = move(newGrid);
    auto moveLeft = [&]() {
        vector<pair<size_t, size_t>*> boxesToMove;
        for (auto& b : boxes) {
            if (b.first == rc - 2 && b.second == rr) boxesToMove.emplace_back(&b);
        }
        bool move = grid[rr][rc - 1] == '.';
        for (size_t i = 0; i < boxesToMove.size(); ++i) {
            auto* bc = boxesToMove[i];
            if (grid[bc->second][bc->first - 1] != '.') {
                move = false;
                break;
            }
            for (auto& b : boxes) {
                if (b.first == bc->first - 2 && b.second == rr) boxesToMove.emplace_back(&b);
            }
        }
        if (move) {
            for (auto& p : boxesToMove) --p->first;
            --rc;
        }
    };
    auto moveRight = [&]() {
        vector<pair<size_t, size_t>*> boxesToMove;
        for (auto& b : boxes) {
            if (b.first == rc + 1 && b.second == rr) boxesToMove.emplace_back(&b);
        }
        bool move = grid[rr][rc + 1] == '.';
        for (size_t i = 0; i < boxesToMove.size(); ++i) {
            auto* bc = boxesToMove[i];
            if (grid[bc->second][bc->first + 2] != '.') {
                move = false;
                break;
            }
            for (auto& b : boxes) {
                if (b.first == bc->first + 2 && b.second == rr) boxesToMove.emplace_back(&b);
            }
        }
        if (move) {
            for (auto& p : boxesToMove) ++p->first;
            ++rc;
        }
    };
    auto moveVertical = [&](int d) {
        vector<pair<size_t, size_t>*> boxesToMove;
        set<pair<size_t, size_t>*> added;
        auto add = [&](pair<size_t, size_t>* b) {
            if (added.count(b) == 0) {
                boxesToMove.emplace_back(b);
                added.emplace(b);
            }
            };
        for (auto& b : boxes) {
            if ((b.first == rc - 1 || b.first == rc) && b.second == rr + d) add(&b);
        }
        bool move = grid[rr + d][rc] == '.';
        for (size_t i = 0; i < boxesToMove.size(); ++i) {
            auto* bc = boxesToMove[i];
            if (grid[bc->second + d][bc->first] != '.' || grid[bc->second + d][bc->first + 1] != '.') {
                move = false;
                break;
            }
            for (auto& b : boxes) {
                if ((b.first >= bc->first - 1 && b.first <= bc->first + 1) && b.second == bc->second + d) add(&b);
            }
        }
        if (move) {
            for (auto& p : boxesToMove) p->second += d;
            rr += d;
        }
    };
    for (auto m : moves) {
        if (m == '<') moveLeft();
        else if (m == '>') moveRight();
        else if (m == '^') moveVertical(-1);
        else if (m == 'v') moveVertical(1);

    }
    int64_t sum = 0;
    for (auto& p : boxes) sum += 100 * p.second + p.first;
    print(sum);
}
}

void p15() {
    p15_1();
    p15_2();
}
