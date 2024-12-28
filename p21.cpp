#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "util.h"

using namespace std;

namespace {
class p21_imlp {
public:
    p21_imlp(int numLevels) : numLevels(numLevels + 1) {}
private:
    vector<string> numGrid = { "789", "456", "123", "#0A" };
    vector<string> keypadGrid = { "#^A", "<v>" };
    map<char, pair<int, int>> numMap = genMaps(numGrid);
    map<char, pair<int, int>> keypadMap = genMaps(keypadGrid);
    map<pair<int, string>, int64_t> mem;
    int numLevels = 0;

    vector<string> getPaths(vector<string> grid, int sr, int sc, char t) {
        vector<string> paths;
        queue<tuple<int, int, string>> q;

        auto add = [&](int r, int c, const string& path, char d) {
            if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == '#') return;
            q.emplace(r, c, path + d);
        };

        q.emplace(sr, sc, "");
        while (!q.empty()) {
            auto [r, c, path] = q.front();
            q.pop();
            if (grid[r][c] == t) {
                paths.emplace_back(path);
                while (!q.empty()) {
                    auto [r, c, path] = q.front();
                    q.pop();
                    if (grid[r][c] == t) paths.emplace_back(path);
                }
                break;
            }

            add(r - 1, c, path, '^');
            add(r + 1, c, path, 'v');
            add(r, c - 1, path, '<');
            add(r, c + 1, path, '>');
        }

        return paths;
    }
    map<char, pair<int, int>> genMaps(const vector<string>& grid) {
        map<char, pair<int, int>> map;
        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[0].size(); ++c) {
                map[grid[r][c]] = { r, c };
            }
        }
        return map;
    }

    int64_t keyPadMove(const string& str, int level) {
        if (level == numLevels) return str.length();
        auto t = make_pair(level, str);
        auto it = mem.find(t);
        if (it != mem.end()) return it->second;
        char prev = 'A';

        int64_t bestLength = 0;
        for (auto& n : str) {
            int64_t best = numeric_limits<int64_t>::max();

            for (const auto& path : getPaths(keypadGrid, keypadMap[prev].first, keypadMap[prev].second, n)) {
                best = min(best, keyPadMove(path + "A", level + 1));
            }
            bestLength += best;
            prev = n;
        }
        mem[t] = bestLength;
        return bestLength;
    }

public:
    int64_t bestLength(const string& str) {
        vector<string> paths = { "" };
        int sr = 3;
        int sc = 2;
        string s;
        for (auto& n : str) {
            vector<string> newPaths;
            for (const auto& path : getPaths(numGrid, sr, sc, n)) {
                for (const auto& p : paths) newPaths.emplace_back(p + path + "A");
            }
            paths = move(newPaths);
            sr = numMap[n].first;
            sc = numMap[n].second;
        }
        int64_t best = numeric_limits<int64_t>::max();
        for (auto& path : paths) {
            best = min(best, keyPadMove(path, 1));
        }

        return best;
    }
};


void p21_1() {
    auto data = readFile(DATA_PATH + "p21.txt");

    int64_t sum = 0;
    for (const auto row : data) {
        sum += p21_imlp(2).bestLength(row) * stoi(row.substr(0, row.length() - 1));
    }
    print(sum);
}

void p21_2() {
    auto data = readFile(DATA_PATH + "p21.txt");

    int64_t sum = 0;
    for (const auto row : data) {
        sum += p21_imlp(25).bestLength(row) * stoi(row.substr(0, row.length() - 1));
    }
    print(sum);
}
}

void p21() {
    p21_1();
    p21_2();
}
