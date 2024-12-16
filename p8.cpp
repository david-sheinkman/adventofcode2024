#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {
struct Point {
	int r;
	int c;

	bool operator<(const Point& other) const {
		return r < other.r || (r == other.r && c < other.c);
	}
};

map<char, vector<Point>> readAntennas(const vector<string>& data) {
	map<char, vector<Point>> antennas;
	for (int r = 0; r < static_cast<int>(data.size()); ++r) {
		for (int c = 0; c < static_cast<int>(data[0].size()); ++c) {
			if (data[r][c] != '.') antennas[data[r][c]].emplace_back(r, c);
		}
	}
	return antennas;
}

void p8_1() {
	auto data = readFile(DATA_PATH + "p8.txt");

	auto antennas = readAntennas(data);
	set<Point> antinodes;
	auto addPoint = [&](const Point& p) {
		if (p.r >= 0 && p.r < data.size() &&
			p.c >= 0 && p.c < data[0].size()) antinodes.emplace(p);
	};
	for (const auto& [a, points] : antennas) {
		for (size_t i = 0; i < points.size(); ++i) {
			for (size_t j = i + 1; j < points.size(); ++j) {
				int dc = abs(points[i].c - points[j].c);
				int dr = abs(points[i].r - points[j].r);
				Point p1, p2;
				if (points[i].r <= points[j].r) {
					p1.r = points[i].r - dr;
					p2.r = points[j].r + dr;
				}
				else {
					p1.r = points[i].r + dr;
					p2.r = points[j].r - dr;
				}
				if (points[i].c <= points[j].c) {
					p1.c = points[i].c - dc;
					p2.c = points[j].c + dc;
				}
				else {
					p1.c = points[i].c + dc;
					p2.c = points[j].c - dc;
				}
				addPoint(p1);
				addPoint(p2);
			}
		}
	}

	print(antinodes.size());
}

void p8_2() {
	auto data = readFile(DATA_PATH + "p8.txt");

	auto antennas = readAntennas(data);
	set<Point> antinodes;
	auto addPoint = [&](const Point& p) {
		if (p.r >= 0 && p.r < data.size() &&
			p.c >= 0 && p.c < data[0].size()) {
			antinodes.emplace(p);
			return true;
		}
		return false;
	};
	for (const auto& [a, points] : antennas) {
		for (size_t i = 0; i < points.size(); ++i) {
			for (size_t j = i + 1; j < points.size(); ++j) {
				int dc = abs(points[i].c - points[j].c);
				int dr = abs(points[i].r - points[j].r);
				Point p1 = points[i];
				Point p2 = points[j];
				bool cont1 = true;
				bool cont2 = true;
				addPoint(points[i]);
				addPoint(points[j]);
				while(cont1 || cont2) {
					if (points[i].r <= points[j].r) {
						p1.r -= dr;
						p2.r += dr;
					}
					else {
						p1.r += dr;
						p2.r -= dr;
					}
					if (points[i].c <= points[j].c) {
						p1.c -= dc;
						p2.c += dc;
					}
					else {
						p1.c += dc;
						p2.c -= dc;
					}
					cont1 = addPoint(p1);
					cont2 = addPoint(p2);
				}
			}
		}
	}

	print(antinodes.size());
}
}

void p8() {
	p8_1();
	p8_2();
}
