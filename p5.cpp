#include <iostream>
#include <set>
#include <map>
#include <vector>

#include "util.h"

using namespace std;

namespace {
map<int, set<int>> extract_rules(const vector<string>& lines, int& l) {
	map<int, set<int>> rules;
	for (; l < lines.size(); ++l) {
		auto items = splitString(lines[l], '|');
		if (items.empty()) break;
		rules[stoi(items[0])].emplace(stoi(items[1]));
	}
	return rules;
}

void p5_1() {
	auto lines = readFile(DATA_PATH + "p5.txt");
	int l = 0;
	auto rules = extract_rules(lines, l);

	int sum = 0;
	for (++l; l < lines.size(); ++l) {
		vector<int> update;
		auto items = splitString(lines[l], ',');
		for (auto item : items) update.emplace_back(stoi(item));
		bool good = true;
		for (size_t i = 0; good && i < update.size(); ++i) {
			for (size_t j = i + 1; j < update.size(); ++j) {
				if (rules[update[i]].count(update[j]) == 0) {
					good = false;
					break;
				}
			}
		}
		if (good) {
			sum += update[update.size() / 2];
		}
	}
	print(sum);
}

void p5_2() {
	auto lines = readFile(DATA_PATH + "p5.txt");
	int l = 0;
	auto rules = extract_rules(lines, l);

	int sum = 0;
	for (++l; l < lines.size(); ++l) {
		vector<int> update;
		auto items = splitString(lines[l], ',');
		for (auto item : items) update.emplace_back(stoi(item));
		bool good = true;
		for (size_t i = 0; good && i < update.size(); ++i) {
			for (size_t j = i + 1; j < update.size(); ++j) {
				if (rules[update[i]].count(update[j]) == 0) {
					good = false;
					break;
				}
			}
		}
		if (!good) {
			vector<int> new_update;
			for (auto n : update) {
				auto iter = new_update.begin();
				for (; iter != new_update.end(); ++iter) {
					if (rules[n].count(*iter) > 0) {
						iter = new_update.insert(iter, n);
						break;
					}
				}
				if (iter == new_update.end()) {
					new_update.push_back(n);
				}
			}
			sum += new_update[new_update.size() / 2];
		}
	}
	print(sum);
}
}

void p5() {
	p5_1();
	p5_2();
}