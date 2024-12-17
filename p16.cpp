#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "util.h"

using namespace std;

namespace {
enum DIRECTION {
    OUT,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const vector<vector<int64_t>> turn_cost = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1000, 1000},
    {0, 0, 0, 1000, 1000},
    {0, 1000, 1000, 0, 0},
    {0, 1000, 1000, 0, 0} };


int64_t pathCost(vector<string> grid, int r, int c, DIRECTION d) {
    using TYPE = tuple<int64_t, int, int, DIRECTION>;
    std::priority_queue<TYPE, std::vector<TYPE>, std::greater<TYPE>> q;
    q.emplace(0, r, c, d);

    while (!q.empty()) {
        auto [cost, r, c, d] = q.top();
        q.pop();
        if (grid[r][c] == 'E') {
            return cost;
        }

        auto add = [&](int r, int c, DIRECTION nd) {
            if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == '#') return;
            if (grid[r][c] != 'E') grid[r][c] = '#';
            q.emplace(cost + turn_cost[d][nd] + 1, r, c, nd);
        };
        if (d != DOWN) add(r - 1, c, UP);
        if (d != UP) add(r + 1, c, DOWN);
        if (d != RIGHT) add(r, c - 1, LEFT);
        if (d != LEFT) add(r, c + 1, RIGHT);
    }
    return 0;
}

    void p16_1() {
        auto grid = readFile(DATA_PATH + "p16.txt");

        for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
            for (int c = 0; c < static_cast<int>(grid[0].size()); ++c) {
                if (grid[r][c] == 'S') {
                    print(pathCost(grid, r, c, RIGHT));
                }
            }
        }
    }

void p16_2() {
    auto grid = readFile(DATA_PATH + "p16.txt");

    using TYPE = tuple<int64_t, int, int, DIRECTION>;
    std::priority_queue<TYPE, std::vector<TYPE>, std::greater<TYPE>> q;

    int64_t bestCost = 0;

    for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
        for (int c = 0; c < static_cast<int>(grid[0].size()); ++c) {
            if (grid[r][c] == 'S') {
                bestCost = pathCost(grid, r, c, RIGHT);
                q.emplace(0, r, c, RIGHT);
            }
        }
    }

    int count = 1;
    auto orginalGrid = grid;
    while (!q.empty()) {
        auto [cost, r, c, d] = q.top();
        q.pop();
        if (grid[r][c] == 'E') {
            break;
        }
        auto pc = pathCost(orginalGrid, r, c, d);
        count += cost + pc == bestCost;
        grid[r][c] = '#';

        auto add = [&](int r, int c, DIRECTION nd) {
            if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == '#') return;
            q.emplace(cost + turn_cost[d][nd] + 1, r, c, nd);
        };
        add(r - 1, c, UP);
        add(r + 1, c, DOWN);
        add(r, c - 1, LEFT);
        add(r, c + 1, RIGHT);
    }
    print(count);

}
}

void p16() {
    p16_1();
    p16_2();
}
