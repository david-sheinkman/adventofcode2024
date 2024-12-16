#include <iostream>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {

void p10_1() {
	auto data = readFile(DATA_PATH + "p10.txt");
	vector<vector<set<pair<size_t, size_t>>>> reach(data.size(), vector<set<pair<size_t, size_t>>>(data[0].size()));
	auto addPoints = [&](size_t r, size_t c, size_t r1, size_t c1) {
		reach[r][c].insert(reach[r1][c1].begin(), reach[r1][c1].end());
	};
	int64_t count = 0;
	for (char i = '0'; i <= '9'; ++i) {
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[0].size(); ++c) {
				if (data[r][c] == i) {
					if (i == '0') reach[r][c].emplace(r, c);
					else {
						if (r != 0 && data[r - 1][c] == i - 1) addPoints(r, c, r - 1, c);
						if (c != 0 && data[r][c - 1] == i - 1) addPoints(r, c, r, c - 1);
						if (r != data.size() - 1 && data[r + 1][c] == i - 1) addPoints(r, c, r + 1, c);
						if (c != data[0].size() - 1 && data[r][c + 1] == i - 1) addPoints(r, c, r, c + 1);
					}
					if (i == '9') count += reach[r][c].size();
				}
			}
		}
	}
	print(count);
}

void p10_2() {
	auto data = readFile(DATA_PATH + "p10.txt");
	vector<vector<int>> reach(data.size(), vector<int>(data[0].size()));
	auto addPoints = [&](size_t r, size_t c, size_t r1, size_t c1) {
		reach[r][c] += reach[r1][c1];
	};
	int64_t count = 0;
	for (char i = '0'; i <= '9'; ++i) {
		for (size_t r = 0; r < data.size(); ++r) {
			for (size_t c = 0; c < data[0].size(); ++c) {
				if (data[r][c] == i) {
					if (i == '0') reach[r][c] = 1;
					else {
						if (r != 0 && data[r - 1][c] == i - 1) addPoints(r, c, r - 1, c);
						if (c != 0 && data[r][c - 1] == i - 1) addPoints(r, c, r, c - 1);
						if (r != data.size() - 1 && data[r + 1][c] == i - 1) addPoints(r, c, r + 1, c);
						if (c != data[0].size() - 1 && data[r][c + 1] == i - 1) addPoints(r, c, r, c + 1);
					}
					if (i == '9') count += reach[r][c];
				}
			}
		}
	}
	print(count);
}
}

void p10() {
	p10_1();
	p10_2();
}
