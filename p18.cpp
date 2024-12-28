#include <iostream>
#include <queue>
#include <vector>

#include "util.h"

using namespace std;

namespace {
int path_cost(vector<string> grid) {
    using TYPE = tuple<int, int, int>;
    std::priority_queue<TYPE, std::vector<TYPE>, std::greater<TYPE>> q;
    auto add = [&](int cost, int r, int c) {
        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] == '.') {
            q.emplace(cost, r, c);
            grid[r][c] = '#';
        }
        };
    add(0, 0, 0);
    while (!q.empty()) {
        auto [cost, r, c] = q.top();
        q.pop();
        if (r == grid.size() - 1 && c == grid[0].size() - 1) {
            return cost;
        }
        ++cost;
        add(cost, r - 1, c);
        add(cost, r + 1, c);
        add(cost, r, c - 1);
        add(cost, r, c + 1);
    }
    return 0;
}

void p18_1() {
    auto data = readFile(DATA_PATH + "p18.txt");
    const int SIZE = 71;
    vector<string> grid(SIZE, string(SIZE, '.'));
    for (int i = 0; i < 1024; ++i) {
        auto v = splitString(data[i], ',');
        grid[stoi(v[1])][stoi(v[0])] = '#';
    }
    print(path_cost(grid));
}

void p18_2() {
    auto data = readFile(DATA_PATH + "p18.txt");
    const int SIZE = 71;
    vector<string> grid(SIZE, string(SIZE, '.'));
    for (size_t i = 0; i < data.size(); ++i) {
        auto v = splitString(data[i], ',');
        grid[stoi(v[1])][stoi(v[0])] = '#';
        if (path_cost(grid) == 0) {
            print(v[0] + "," + v[1]);
            break;
        }
    }
}
}

void p18() {
    p18_1();
    p18_2();
}
