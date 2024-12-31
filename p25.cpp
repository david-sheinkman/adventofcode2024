#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p25_1() {
    auto data = readFile(DATA_PATH + "p25.txt");
    vector<vector<int>> keys;
    vector<vector<int>> locks;
    int height = 0;
    for (size_t line = 0; line < data.size(); ++line) {
        vector<string> grid;
        for (; line < data.size() && !data[line].empty(); ++line) {
            grid.emplace_back(data[line]);
        }
        height = static_cast<int>(grid.size()) - 2;
        bool isLock = (grid[0][0] == '#');
        auto& vec = isLock ? locks.emplace_back() : keys.emplace_back();
        for (size_t c = 0; c < grid[0].size(); ++c) {
            auto& h = vec.emplace_back(1);
            for (; h < grid.size() - 1; ++h) {
                if (grid[h][c] != grid[0][c]) break;
            }
            --h;
            if (!isLock) h = static_cast<int>(grid.size()) - 2 - h;
        }
    }
    int64_t count = 0;
    for (const auto& lock : locks) {
        for (const auto& key : keys) {
            bool fit = true;
            for (size_t i = 0; i < lock.size(); ++i) {
                if (lock[i] + key[i] > height) {
                    fit = false;
                    break;
                }
            }
            count += fit;
        }
    }
    print(count);
}

void p25_2() {
}
}

void p25() {
    p25_1();
    p25_2();
}
