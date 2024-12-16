#include <iostream>
#include <stack>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p12_1() {
	auto data = readFile(DATA_PATH + "p12.txt");
	vector<vector<bool>> visited(data.size(), vector<bool>(data[0].size()));
	int64_t sum = 0;
	for (int r = 0; r < static_cast<int>(data.size()); ++r) {
		for (int c = 0; c < static_cast<int>(data[0].size()); ++c) {
			int area = 0;
			int perimeter = 0;
			auto region = data[r][c];
			stack<pair<int, int>> s;
			auto add = [&](int r, int c) {
				if (r >= 0 && c >= 0 && r < data.size() && c < data[0].size()) {
					if (data[r][c] == region && !visited[r][c]) {
						visited[r][c] = true;
						s.emplace(r, c);
					}
					else if (data[r][c] != region) ++perimeter;
				} else ++perimeter;
			};
			add(r, c);
			while (!s.empty()) {
				auto [r, c] = s.top();
				s.pop();
					
				++area;
				add(r - 1, c);
				add(r + 1, c);
				add(r, c - 1);
				add(r, c + 1);
			}
			sum += area * perimeter;
		}
	}

	print(sum);
}

void p12_2() {
	auto data = readFile(DATA_PATH + "p12.txt");
	vector<vector<bool>> visited(data.size(), vector<bool>(data[0].size()));
	int64_t sum = 0;
	for (int r = 0; r < static_cast<int>(data.size()); ++r) {
		for (int c = 0; c < static_cast<int>(data[0].size()); ++c) {
			int area = 0;
			int perimeter = 0;
			auto region = data[r][c];
			auto notRegion = [&](int r, int c) {
				return r < 0 || c < 0 || r >= data.size() || c >= data.size() || data[r][c] != region;
			};

			if (!visited[r][c]) {
				stack<pair<int, int>> s;
				auto add = [&](int r, int c) {
					if (r >= 0 && c >= 0 && r < data.size() && c < data[0].size()) {
						if (data[r][c] == region && !visited[r][c]) {
							visited[r][c] = true;
							s.emplace(r, c);

							perimeter += (notRegion(r - 1, c) && notRegion(r, c - 1)) || (!notRegion(r, c - 1) && notRegion(r - 1, c) && !notRegion(r - 1, c - 1));
							perimeter += (notRegion(r - 1, c) && notRegion(r, c - 1)) || (notRegion(r, c - 1) && !notRegion(r - 1, c) && !notRegion(r - 1, c - 1));
							perimeter += (notRegion(r + 1, c) && notRegion(r, c - 1)) || (!notRegion(r, c - 1) && notRegion(r + 1, c) && !notRegion(r + 1, c - 1));
							perimeter += (notRegion(r - 1, c) && notRegion(r, c + 1)) || (notRegion(r, c + 1) && !notRegion(r - 1, c) && !notRegion(r - 1, c + 1));
						}
					}
				};
				add(r, c);
				while (!s.empty()) {
					auto [r, c] = s.top();
					s.pop();

					++area;
					add(r - 1, c);
					add(r + 1, c);
					add(r, c - 1);
					add(r, c + 1);
				}
				sum += area * perimeter;
			}
		}
	}

	print(sum);
}
}

void p12() {
	p12_1();
	p12_2();
}
