#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p1_1() {
	vector<int> l1, l2;
	for (const auto& line : readFile(DATA_PATH + "p1.txt")) {
		auto items = splitString(line, ' ');
		l1.emplace_back(stoi(items[0]));
		l2.emplace_back(stoi(items[1]));
	}
	std::sort(l1.begin(), l1.end());
	std::sort(l2.begin(), l2.end());
	int64_t sum = 0;
	for (size_t i = 0; i < l1.size(); ++i) {
		sum += abs(l1[i] - l2[i]);
	}
	print(sum);
}

void p1_2() {
	map<int, int> m1, m2;
	for (const auto& line : readFile(DATA_PATH + "p1.txt")) {
		auto items = splitString(line, ' ');
		++m1[stoi(items[0])];
		++m2[stoi(items[1])];
	}
	int64_t sum = 0;
	for (auto [k, c] : m1) {
		sum += k * c * m2[k];
	}
	print(sum);
}
}

void p1() {
	p1_1();
	p1_2();
}
