#include <fstream>
#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p14_1() {
    vector<int> quadrants(4);
    const int64_t width = 101;
    const int64_t height = 103;
    const int64_t midx = width / 2;
    const int64_t midy = height / 2;

    const int steps = 100;
    for (const auto& row : readFile(DATA_PATH + "p14.txt")) {
        auto v = extractInts(row, "p=([0-9]*),([0-9]*) v=(-?[0-9]*),(-?[0-9]*)");
        v[0] = (v[0] + steps * v[2]) % width;
        v[1] = (v[1] + steps * v[3]) % height;
        if (v[0] < 0) v[0] += width;
        if (v[1] < 0) v[1] += height;
        if (v[0] != midx && v[1] != midy) {
            if (v[1] < midy) {
                if (v[0] < midx) ++quadrants[0];
                else ++quadrants[1];
            }
            else {
                if (v[0] < midx) ++quadrants[2];
                else ++quadrants[3];
            }
        }
    }
    print(quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3]);
}

void p14_2() {
    const int64_t width = 101;
    const int64_t height = 103;
    const int64_t midx = width / 2;
    const int64_t midy = height / 2;
    vector<vector<int64_t>> robots;

    for (const auto& row : readFile(DATA_PATH + "p14.txt")) {
        robots.emplace_back(extractInts(row, "p=([0-9]*),([0-9]*) v=(-?[0-9]*),(-?[0-9]*)"));
    }
    ofstream file;
    file.open("p14out.txt");

    for (int step = 1; step < 10000; ++step) {
        vector<vector<int>> grid(height, vector<int>(width));
        for (auto& v : robots) {
            v[0] = (v[0] + v[2]) % width;
            v[1] = (v[1] + v[3]) % height;
            if (v[0] < 0) v[0] += width;
            if (v[1] < 0) v[1] += height;
            ++grid[v[1]][v[0]];
        }
        if ((step - 31) % 103 == 0) {
            file << "\n\n\n\n";
            file << step << "\n";
            for (const auto& row : grid) {
                for (auto c : row) {
                    if (c == 0) file << " ";
                    else file << c;
                }
                file << endl;
            }
        }
    }
    file.close();
}
}

void p14() {
    p14_1();
    p14_2();
}
