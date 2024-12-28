#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {
int64_t applyProcess(int64_t n) {
    n = ((n * 64) ^ n) % 16777216;
    n = ((n / 32) ^ n) % 16777216;
    return ((n * 2048) ^ n) % 16777216;
}

void p22_1() {
    int64_t sum = 0;
    for (const auto& str : readFile(DATA_PATH + "p22.txt")) {
        int64_t n = stoll(str);
        for (int i = 0; i < 2000; ++i) n = applyProcess(n);
        sum += n;
    }
    print(sum);
}

void p22_2() {
    map<string, int64_t> sums;
    for (const auto& str : readFile(DATA_PATH + "p22.txt")) {
        int64_t n = stoll(str);
        vector<int64_t> p;
        vector<int64_t> d;
        int64_t previousPrice = n % 10;
        for (int i = 0; i < 2000; ++i) {
            n = applyProcess(n);
            int64_t price = n % 10;
            p.emplace_back(price);
            d.emplace_back(price - previousPrice);
            previousPrice = price;
        }
        set<string> inserted;
        for (int i = 0; i < d.size() - 3; ++i) {
            string str = to_string(d[i]);
            for (int j = 1; j < 4; ++j) str += to_string(d[i + j]);
            if (inserted.count(str) == 0) {
                sums[str] += p[i + 3];
                inserted.insert(str);
            }
        }
    }
    int64_t bestSolution = 0;
    for (const auto& [str, sum] : sums) {
        bestSolution = max(bestSolution, sum);
    }
    print(bestSolution);
}
}

void p22() {
    p22_1();
    p22_2();
}
