#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {

int read_int(const string& s, size_t& pos) {
	int num = 0;
	for (int i = 0; i < 3; ++i, ++pos) {
		if (isdigit(s[pos])) num = num * 10 + s[pos] - '0';
		else return num;
	}
	return num;
};

void p3_1() {
	auto str = readFile(DATA_PATH + "p3.txt")[0];
	
	int64_t sum = 0;
	for (size_t l= 0; l < str.size(); ++l) {
		if (str.substr(l, 4) == "mul(") {
			l += 4;
			if (isdigit(str[l])) {
				int n1 = read_int(str, l);
				if (str[l] == ',' && isdigit(str[l + 1])) {
					++l;
					int n2 = read_int(str, l);
					if (str[l] == ')') sum += n1 * n2;
				}
			}
		}
	}
	print(sum);
}

void p3_2() {
	auto str = readFile(DATA_PATH + "p3.txt")[0];

	int64_t sum = 0;
	bool enabled = true;
	for (size_t l = 0; l < str.size(); ++l) {
		if (str.substr(l, 4) == "do()") {
			enabled = true;
			l += 3;
		}
		else if (str.substr(l, 7) == "don't()") {
			enabled = false;
			l += 6;
		}
		else if (str.substr(l, 4) == "mul(") {
			l += 4;
			if (isdigit(str[l])) {
				int n1 = read_int(str, l);
				if (str[l] == ',' && isdigit(str[l + 1])) {
					++l;
					int n2 = read_int(str, l);
					if (str[l] == ')' && enabled) sum += n1 * n2;
				}
			}
		}
	}
	print(sum);
}
}

void p3() {
	p3_1();
	p3_2();
}