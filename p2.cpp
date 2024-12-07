#include <iostream>

#include "util.h"

using namespace std;

namespace {
bool is_safe(vector<int> levels) {
	enum DIRECTION {
		NONE, INCREASING, DECREASING
	};

	int previous = levels[0];
	int direction = NONE;
	for (size_t i = 1; i < levels.size(); ++i) {
		int num = levels[i];
		int diff = num - previous;
		if (diff == 0 || abs(diff) > 3)
			return false;

		if (direction == NONE)
			direction = diff > 0 ? INCREASING : DECREASING;
		else if ((direction == INCREASING && diff < 0) || (direction == DECREASING && diff > 0))
			return false;

		previous = num;
	}
	return true;

}
void p2_1() {
	int safe_count = 0;
	for (const auto& line : readFile(DATA_PATH + "p2.txt")) {
		vector<int> levels;
		for (const auto& s : splitString(line, ' ')) levels.emplace_back(stoi(s));

		safe_count += is_safe(levels);
	}
	print(safe_count);
}
void p2_2() {
	int safe_count = 0;
	for (const auto& line : readFile(DATA_PATH + "p2.txt")) {
		vector<int> levels;
		for (const auto& s : splitString(line, ' ')) levels.emplace_back(stoi(s));

		if (is_safe(levels)) {
			++safe_count;
		}
		else {
			for (size_t i = 0; i < levels.size(); ++i) {
				auto new_levels = levels;
				new_levels.erase(new_levels.begin() + i);
				if (is_safe(new_levels)) {
					++safe_count;
					break;
				}
			}
		}

	}
	print(safe_count);
}
}

void p2() {
	p2_1();
	p2_2();
}