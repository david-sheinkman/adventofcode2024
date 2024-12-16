#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p4_1() {
	auto data = readFile(DATA_PATH + "p4.txt");

	auto comp = [&data](int r1, int c1, int r2, int c2, int r3, int c3) {
		return r1 >= 0 && r1 < data.size() &&
			r2 >= 0 && r2 < data.size() &&
			r3 >= 0 && r3 < data.size() &&
			c1 >= 0 && c1 < data[0].size() &&
			c2 >= 0 && c2 < data[0].size() &&
			c3 >= 0 && c3 < data[0].size() && data[r1][c1] == 'M' && data[r2][c2] == 'A' && data[r3][c3] == 'S';
		};

	int count = 0;
	for (int r = 0; r < static_cast<int>(data.size()); ++r) {
		for (int c = 0; c < static_cast<int>(data[0].size()); ++c) {
			if (data[r][c] == 'X') {
				count += comp(r, c + 1, r, c + 2, r, c + 3);
				count += comp(r, c - 1, r, c - 2, r, c - 3);
				count += comp(r + 1, c + 1, r + 2, c + 2, r + 3, c + 3);
				count += comp(r - 1, c + 1, r - 2, c + 2, r - 3, c + 3);
				count += comp(r + 1, c, r + 2, c, r + 3, c);
				count += comp(r - 1, c, r - 2, c, r - 3, c);
				count += comp(r + 1, c - 1, r + 2, c - 2, r + 3, c - 3);
				count += comp(r - 1, c - 1, r - 2, c - 2, r - 3, c - 3);
			}
		}
	}
	print(count);
}

void p4_2() {
	auto data = readFile(DATA_PATH + "p4.txt");

	auto comp = [&data](int r1, int c1, int r2, int c2) {
		return r1 >= 0 && r1 < data.size() &&
			r2 >= 0 && r2 < data.size() &&
			c1 >= 0 && c1 < data[0].size() &&
			c2 >= 0 && c2 < data[0].size() && 
			((data[r1][c1] == 'M' && data[r2][c2] == 'S') || (data[r1][c1] == 'S' && data[r2][c2] == 'M'));
		};

	int count = 0;
	for (int r = 0; r < static_cast<int>(data.size()); ++r) {
		for (int c = 0; c < static_cast<int>(data[0].size()); ++c) {
			if (data[r][c] == 'A') {
				count += comp(r - 1, c - 1, r + 1, c + 1) && comp(r + 1, c - 1, r - 1, c + 1);
			}
		}
	}
	print(count);
}
}

void p4() {
	p4_1();
	p4_2();
}
