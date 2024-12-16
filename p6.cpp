#include <iostream>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {
enum DIRECTION {
	OUT,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void p6_1() {
	auto data = readFile(DATA_PATH + "p6.txt");
	size_t pr = 0;
	size_t pc = 0;
	auto direction = UP;
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 0; c < data[0].size(); ++c) {
			if (data[r][c] == '^') {
				pr = r;
				pc = c;
				break;
			}
		}
	}
	data[pr][pc] = 'X';
	while (direction != OUT) {
		switch (direction) {
		case UP:
			if (pr == 0) direction = OUT;
			else if (data[pr - 1][pc] == '#') direction = RIGHT;
			else data[--pr][pc] = 'X';
			break;
		case DOWN:
			if (pr == data.size() - 1) direction = OUT;
			else if (data[pr + 1][pc] == '#') direction = LEFT;
			else data[++pr][pc] = 'X';
			break;
		case LEFT:
			if (pc == 0) direction = OUT;
			else if (data[pr][pc - 1] == '#') direction = UP;
			else data[pr][--pc] = 'X';
			break;
		case RIGHT:
			if (pc == data[0].size() - 1) direction = OUT;
			else if (data[pr][pc + 1] == '#') direction = DOWN;
			else data[pr][++pc] = 'X';
			break;
		}
	}

	int count = 0;
	for (const auto& row : data) {
		for (const auto c : row) {
			count += c == 'X';
		}
	}
	print(count);
}

bool has_loop(const vector<string>& data, size_t pr, size_t pc, DIRECTION direction) {
	set<tuple<size_t, size_t, DIRECTION>> visited;
	while (direction != OUT) {
		tuple<size_t, size_t, DIRECTION> t = { pr, pc, direction };
		if (visited.count(t) > 0) return true;
		visited.emplace(t);
		switch (direction) {
		case UP:
			if (pr == 0) direction = OUT;
			else if (data[pr - 1][pc] == '#') direction = RIGHT;
			else --pr;
			break;
		case DOWN:
			if (pr == data.size() - 1) direction = OUT;
			else if (data[pr + 1][pc] == '#') direction = LEFT;
			else ++pr;
			break;
		case LEFT:
			if (pc == 0) direction = OUT;
			else if (data[pr][pc - 1] == '#') direction = UP;
			else --pc;
			break;
		case RIGHT:
			if (pc == data[0].size() - 1) direction = OUT;
			else if (data[pr][pc + 1] == '#') direction = DOWN;
			else ++pc;
			break;
		}
	}
	return false;
}

void p6_2() {
	auto data = readFile(DATA_PATH + "p6.txt");
	size_t pr = 0;
	size_t pc = 0;
	size_t opr = 0;
	size_t opc = 0;
	auto direction = UP;
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 0; c < data[0].size(); ++c) {
			if (data[r][c] == '^') {
				pr = opr = r;
				pc = opc = c;
				break;
			}
		}
	}
	while (direction != OUT) {
		switch (direction) {
		case UP:
			if (pr == 0) direction = OUT;
			else if (data[pr - 1][pc] == '#') direction = RIGHT;
			else data[--pr][pc] = 'X';
			break;
		case DOWN:
			if (pr == data.size() - 1) direction = OUT;
			else if (data[pr + 1][pc] == '#') direction = LEFT;
			else data[++pr][pc] = 'X';
			break;
		case LEFT:
			if (pc == 0) direction = OUT;
			else if (data[pr][pc - 1] == '#') direction = UP;
			else data[pr][--pc] = 'X';
			break;
		case RIGHT:
			if (pc == data[0].size() - 1) direction = OUT;
			else if (data[pr][pc + 1] == '#') direction = DOWN;
			else data[pr][++pc] = 'X';
			break;
		}
	}
	int count = 0;
	data[opr][opc] = '^';
	for (size_t r = 0; r < data.size(); ++r) {
		for (size_t c = 0; c < data[0].size(); ++c) {
			if (data[r][c] == 'X') {
				data[r][c] = '#';
				count += has_loop(data, opr, opc, UP);
				data[r][c] = '.';
			}
		}
	}
	print(count);
}
}

void p6() {
	p6_1();
	p6_2();
}
