#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {

bool p7_impl(const vector<int64_t>& vec, int64_t target, size_t i, int64_t value, bool allowConcat) {
	if (i == vec.size()) return value == target;
	if (p7_impl(vec, target, i + 1, value + vec[i], allowConcat)) return true;
	if (i != 0 && p7_impl(vec, target, i + 1, value * vec[i], allowConcat)) return true;
	if (allowConcat) {
		for (int64_t t = vec[i]; t != 0; t /= 10) value *= 10;
		value += vec[i];
		if (p7_impl(vec, target, i + 1, value, allowConcat)) return true;
	}
	return false;
}

void p7_1() {
	int64_t sum = 0;
	for (const auto& line : readFile(DATA_PATH + "p7.txt")) {
		auto items = splitString(line, ':');
		int64_t target = stoll(items[0]);
		auto vec = stringToInt64Vec(splitString(items[1], ' '));
		if (p7_impl(vec, target, 0, 0, false)) sum += target;
	}
	print(sum);
}

void p7_2() {
	int64_t sum = 0;
	for (const auto& line : readFile(DATA_PATH + "p7.txt")) {
		auto items = splitString(line, ':');
		int64_t target = stoll(items[0]);
		auto vec = stringToInt64Vec(splitString(items[1], ' '));
		if (p7_impl(vec, target, 0, 0, true)) sum += target;
	}
	print(sum);
}
}

void p7() {
	p7_1();
	p7_2();
}
