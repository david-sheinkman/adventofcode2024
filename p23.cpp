#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p23_1() {
    auto data = readFile(DATA_PATH + "p23.txt");
    map<string, set<string>> nodeMap;
    for (const auto& row : data) {
        auto v = splitString(row, '-');
        nodeMap[v[0]].emplace(v[1]);
        nodeMap[v[1]].emplace(v[0]);
    }
    vector<string> nodes;
    int count = 0;
    for (const auto& [k, v] : nodeMap) nodes.emplace_back(k);
    for (const auto& [n, edgeSet] : nodeMap) {
        vector<string> edges(edgeSet.begin(), edgeSet.end());
        for (size_t i = 0; i < edges.size(); ++i) {
            if (edges[i] < n) continue;
            auto& s = nodeMap[edges[i]];
            for (size_t j = i + 1; j < edges.size(); ++j) {
                if (s.find(edges[j]) != s.end()) {
                    if (n[0] == 't' || edges[i][0] == 't' || edges[j][0] == 't') ++count;
                }
            }
        }
    }
    print(count);
}

void p23_2() {
    auto data = readFile(DATA_PATH + "p23.txt");
    map<string, set<string>> nodeMap;
    for (const auto& row : data) {
        auto v = splitString(row, '-');
        nodeMap[v[0]].emplace(v[1]);
        nodeMap[v[1]].emplace(v[0]);
    }

    set<string> largestSet;
    for (const auto& [n, edgeSet] : nodeMap) {
        vector<set<string>> setList = { {n} };
        for (const auto& n1 : edgeSet) {
            size_t setSize = setList.size(); 
            for (size_t i = 0; i < setSize; ++i) {
                const auto& s = setList[i];
                bool connected = true;
                for (const auto& n2 : s) {
                    if (nodeMap[n2].count(n1) == 0) {
                        connected = false;
                    }
                }
                if (connected) {
                    auto newSet = s;
                    newSet.insert(n1);
                    setList.emplace_back(newSet);
                }
            }
        }
        for (const auto& s : setList) {
            if (s.size() > largestSet.size()) largestSet = s;
        }
    }
    string sol;
    string sep;
    for (const auto& n : largestSet) {
        sol += sep;
        sol += n;
        sep = ",";
    }
    print(sol);
}
}

void p23() {
    p23_1();
    p23_2();
}
