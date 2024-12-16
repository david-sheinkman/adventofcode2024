#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {

struct File {
	int id = 0;
	int count = 0;
	int start = 0;
	bool operator==(const File& rhs) {
		return id == rhs.id && count == rhs.count;
	}
	bool operator!=(const File& rhs) {
		return !(*this == rhs);
	}
};

void p9_1() {
	auto line = readFile(DATA_PATH + "p9.txt")[0];
	vector<File> files;
	bool freeSpace = false;
	int id = 0;
	vector<int> v;
	for (auto c : line) {
		if (!freeSpace) {
			for (int i = 0; i < c - '0'; ++i) v.emplace_back(id);
			files.emplace_back(id++, c - '0');
		}else {
			for (int i = 0; i < c - '0'; ++i) v.emplace_back(-1);
		}
		freeSpace = !freeSpace;
	}

	int64_t i = 0;
	int64_t j = v.size() - 1;
	while (i != j) {
		if (v[i] == -1) {
			if (v[j] != -1) {
				v[i] = v[j];
				v[j] = -1;
				++i;
			}
			--j;
		}
		else ++i;
	}

	int64_t sum = 0;
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i] != -1) sum += i * v[i];
	}
	print(sum);
	return;
	{

		int64_t sum = 0;
		int64_t id = 0;
		File posL;
		File posR = files.back();
		freeSpace = false;
		for (auto c : line) {
			int n = c - '0';
			if (freeSpace) {
				for (int i = 0; i < n && posL != posR; ++i, ++id) {
					sum += id * posR.id;
					--posR.count;
					if (posR.count == 0) {
						--posR.id;
						posR.count = files[posR.id].count;
					}
				}
			}
			else {
				if (posL.count == files[posL.id].count) {
					++posL.id;
					posL.count = 0;
				}
				for (int i = 0; i < n && posL != posR; ++i, ++id, posL.count++) {
					sum += id * posL.id;
				}
			}
			freeSpace = !freeSpace;
		}
	}
	print(sum);
}

void p9_2() {
	auto line = readFile(DATA_PATH + "p9.txt")[0];
	bool freeSpace = false;
	vector<File> files;
	vector<File> freeSpaces;
	int id = 0;
	int start = 0;
	int s = 0;
	for (auto c : line) {
		int n = c - '0';
		s += n;
		if (!freeSpace) files.emplace_back(id++, n, start);
		else freeSpaces.emplace_back(0, n, start);
		start += n;
		freeSpace = !freeSpace;
	}

	for (auto it = files.rbegin(); it != files.rend(); ++it) {
		for (auto& space : freeSpaces) {
			if (space.start > it->start) break;
			if (space.count >= it->count) {
				it->start = space.start;
				space.start += it->count;
				space.count -= it->count;
				break;
			}
		}
	}


	int64_t sum = 0;
	for (auto file : files) {
		for (int i = 0; i < file.count; ++i) {
			sum += file.id * (file.start + i);
		}
	}
	print(sum);
}
}

void p9() {
	p9_1();
	p9_2();
}
