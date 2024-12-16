#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p13_impl(const string& path, int64_t add_value) {
    auto data = readFile(path);

    int64_t cost = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        const auto a = extractInts(data[i++], "Button A: X\\+([0-9]*), Y\\+([0-9]*)");
        const auto b = extractInts(data[i++], "Button B: X\\+([0-9]*), Y\\+([0-9]*)");
        auto p = extractInts(data[i++], "Prize: X=([0-9]*), Y=([0-9]*)");
        p[0] += add_value;
        p[1] += add_value;

        int64_t det = a[0] * b[1] - b[0] * a[1];
        if (det != 0) {
            int64_t x = (p[0] * b[1] - b[0] * p[1]) / det;
            int64_t y = (a[0] * p[1] - p[0] * a[1]) / det;
            int64_t x1 = a[0] * x + b[0] * y;
            int64_t y1 = a[1] * x + b[1] * y;
            if (x1 == p[0] && y1 == p[1]) cost += 3 * x + y;
        }
        else {
            int64_t m = p[0] / b[0];
            int64_t x1 = b[0] * m;
            int64_t y1 = b[1] * m;
            if (x1 == p[0] && y1 == p[1]) cost += m;
        }
    }
    print(cost);
}
void p13_1() {
    p13_impl(DATA_PATH + "p13.txt", 0);
}

void p13_2() {
    p13_impl(DATA_PATH + "p13.txt", 10000000000000);
}
}

void p13() {
	p13_1();
	p13_2();
}
