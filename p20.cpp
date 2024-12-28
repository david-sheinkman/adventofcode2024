#include <iostream>
#include <queue>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p20_1() {
    auto grid = readFile(DATA_PATH + "p20.txt");
    using TYPE = tuple<int, int, int, vector<pair<int, int>>>;
    std::priority_queue<TYPE, std::vector<TYPE>, std::greater<TYPE>> q;
    auto add = [&](int cost, int r, int c, const vector<pair<int, int>>& path) {
        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] != '#') {
            q.emplace(cost, r, c, path);
            if (grid[r][c] != 'E') grid[r][c] = '#';
        }
    };
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 'S') {
                add(0, r, c, vector<pair<int, int>>{});
            }
        }
    }
    vector<vector<int>> pathGrid(grid.size(), vector<int>(grid[0].size(), -1));
    while (!q.empty()) {
        auto [cost, r, c, path] = q.top();
        q.pop();
        path.emplace_back(r, c);
        if (grid[r][c] == 'E') {
            for (int i = 0; i < path.size(); ++i) {
                auto [r, c] = path[i];
                pathGrid[r][c] = i;
            }
            break;
        }
        ++cost;
        add(cost, r - 1, c, path);
        add(cost, r + 1, c, path);
        add(cost, r, c - 1, path);
        add(cost, r, c + 1, path);
    }
    int64_t count = 0;
    auto checkVals = [&](int r1, int c1, int r2, int c2) {
        if (r2 >= 0 && r2 < pathGrid.size() && c2 >= 0 && c2 < pathGrid[0].size() && pathGrid[r2][c2] != -1) {
            int d = abs(pathGrid[r1][c1] - pathGrid[r2][c2]) - 2;
            count += d >= 100;
        }
    };
    for (int r = 0; r < pathGrid.size(); ++r) {
        for (int c = 0; c < pathGrid[0].size(); ++c) {
            if (pathGrid[r][c] != -1) {
                checkVals(r, c, r - 2, c);
                checkVals(r, c, r, c - 2);
            }
        }
    }
    print(count);
}

void p20_2() {
    auto grid = readFile(DATA_PATH + "p20.txt");
    using TYPE = tuple<int, int, int, vector<pair<int, int>>>;
    std::priority_queue<TYPE, std::vector<TYPE>, std::greater<TYPE>> q;
    auto add = [&](int cost, int r, int c, const vector<pair<int, int>>& path) {
        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] != '#') {
            q.emplace(cost, r, c, path);
            if (grid[r][c] != 'E') grid[r][c] = '#';
        }
    };
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 'S') {
                add(0, r, c, vector<pair<int, int>>{});
            }
        }
    }
    vector<vector<int>> pathGrid(grid.size(), vector<int>(grid[0].size(), -1));
    while (!q.empty()) {
        auto [cost, r, c, path] = q.top();
        q.pop();
        path.emplace_back(r, c);
        if (grid[r][c] == 'E') {
            for (int i = 0; i < path.size(); ++i) {
                auto [r, c] = path[i];
                pathGrid[r][c] = i;
            }
            break;
        }
        ++cost;
        add(cost, r - 1, c, path);
        add(cost, r + 1, c, path);
        add(cost, r, c - 1, path);
        add(cost, r, c + 1, path);
    }
    int64_t count = 0;
    auto checkVals = [&](int r1, int c1, int r2, int c2, int a) {
        if (r2 >= 0 && r2 < pathGrid.size() && c2 >= 0 && c2 < pathGrid[0].size() && pathGrid[r2][c2] != -1) {
            int d = abs(pathGrid[r1][c1] - pathGrid[r2][c2]) - a;
            count += d >= 100;
        }
    };
    for (int r = 0; r < pathGrid.size(); ++r) {
        for (int c = 0; c < pathGrid[0].size(); ++c) {
            if (pathGrid[r][c] == -1) continue;
            for (int i = -20; i <= 20; ++i) {
                for (int j = -(20 - abs(i)); abs(i) + abs(j) <= 20; ++j) {
                    checkVals(r, c, r + i, c + j, abs(i) + abs(j));
                }
            }
        }
    }
    count /= 2;
    print(count);
}
}

void p20() {
    p20_1();
    p20_2();
}
