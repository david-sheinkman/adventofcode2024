#include <iostream>
#include <map>
#include <vector>

#include "util.h"

using namespace std;

namespace {
struct p11_impl {
	map<int, map<int64_t, int64_t>> mem;
	int64_t impl(int64_t stone, int level) {
		if (level == 0) return 1;
		auto& levelMem = mem[level];
		auto it = levelMem.find(stone);
		if (it != levelMem.end()) return it->second;
		--level;
		int64_t c = 0;
		if (stone == 0) c = impl(1, level);
		else {
			string s = to_string(stone);
			if (s.size() % 2 == 0) {
				c += impl(stoll(s.substr(0, s.size() / 2)), level);
				c += impl(stoll(s.substr(s.size() / 2)), level);
			}
			else c += impl(stone * 2024, level);
		}
		levelMem[stone] = c;
		return c;
	}

	void run(const string& str, int level) {
		vector<int64_t> stones = stringToInt64Vec(splitString(str, ' '));
		int64_t count = 0;
		for (auto stone : stones) {
			count += impl(stone, level);
		}
		print(count);

	}
};

void p11_1() {
	auto str = readFile(DATA_PATH + "p11.txt")[0];
	p11_impl{}.run(str, 25);
}

void p11_2() {
	auto str = readFile(DATA_PATH + "p11.txt")[0];
	p11_impl{}.run(str, 75);
}
}

void p11() {
	p11_1();
	p11_2();
}
