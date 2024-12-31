#include <iostream>
#include <map>
#include <optional>
#include <queue>
#include <set>
#include <vector>

#include "util.h"

using namespace std;

namespace {
enum GATE_TYPE {
    INITIAL,
    AND,
    OR,
    XOR
};
struct Gate {
    string key;
    string name;
    optional<bool> value;
    bool processed = false;
    GATE_TYPE type = INITIAL;
    string input1;
    string input2;
    vector<string> outputs;
};

void readProgram(string path, queue<string>& toProcess, map<string, Gate>& gateMap) {
    auto data = readFile(DATA_PATH + "p24.txt");
    size_t line = 0;
    for (; line < data.size(); ++line) {
        if (data[line].empty()) break;
        auto v = splitString(data[line], ':');
        auto& gate = gateMap[v[0]];
        gate.key = v[0];
        gate.name = v[0];
        gate.processed = true;
        gate.type = INITIAL;
        gate.value = stoi(v[1]);
        toProcess.emplace(v[0]);
    }
    for (++line; line < data.size(); ++line) {
        auto v = splitString(data[line], ' ');
        auto& gate = gateMap[v[4]];
        gate.key = v[4];
        gate.name = v[4];
        if (v[1] == "AND") gate.type = AND;
        else if (v[1] == "OR") gate.type = OR;
        else if (v[1] == "XOR") gate.type = XOR;
        gate.input1 = v[0];
        gate.input2 = v[2];
        gateMap[gate.input1].outputs.emplace_back(v[4]);
        gateMap[gate.input2].outputs.emplace_back(v[4]);
    }
}

int64_t runProgram(queue<string> toProcess, map<string, Gate> gateMap) {
    while (!toProcess.empty()) {
        auto g = toProcess.front();
        auto& gate = gateMap[g];
        toProcess.pop();
        auto value = [&](const string& g) {
            if (!gateMap[g].value) throw logic_error("unset");
            return gateMap[g].value.value();
        };
        if (gate.type == AND) gate.value = value(gate.input1) && value(gate.input2);
        else if (gate.type == OR) gate.value = value(gate.input1) || value(gate.input2);
        else if (gate.type == XOR) gate.value = value(gate.input1) ^ value(gate.input2);
        for (const auto& output : gate.outputs) {
            auto& outputGate = gateMap[output];
            if (!outputGate.processed && gateMap[outputGate.input1].value.has_value() && gateMap[outputGate.input2].value.has_value()) {
                outputGate.processed = true;
                toProcess.emplace(output);
            }
        }
    }

    int64_t sol = 0;
    for (const auto& [name, gate] : gateMap) {
        if(!gate.value) throw logic_error("unset");
        if (name[0] == 'z') sol |= static_cast<int64_t>(gate.value.value()) << stoi(name.substr(1));
    }
    return sol;
}
void getDeps(map<string, Gate>& gateMap, vector<string>& list, const string& gate) {
    const auto& g = gateMap[gate];
    string prefix;
    if (g.type == AND) prefix = "&";
    else if (g.type == OR) prefix = "|";
    else if (g.type == XOR) prefix = "^";

    list.emplace_back(prefix + g.name);
    if (g.type != INITIAL) {
        getDeps(gateMap, list, g.input1);
        getDeps(gateMap, list, g.input2);
    }
    return;
    if (g.type != INITIAL) {
        if (gateMap[g.input1].type == gateMap[g.input2].type) {
            if (g.input1 < g.input2) {
                getDeps(gateMap, list, g.input1);
                getDeps(gateMap, list, g.input2);
            }
            else {
                getDeps(gateMap, list, g.input2);
                getDeps(gateMap, list, g.input1);

            }
        }
        else if (gateMap[g.input1].type <= gateMap[g.input2].type) {
            getDeps(gateMap, list, g.input1);
            getDeps(gateMap, list, g.input2);
        }
        else {
            getDeps(gateMap, list, g.input2);
            getDeps(gateMap, list, g.input1);

        }
    }
};

void p24_1() {
    queue<string> toProcess;
    map<string, Gate> gateMap;
    readProgram(DATA_PATH + "p24.txt", toProcess, gateMap);
    print(runProgram(toProcess, gateMap));
}

void p24_2() {
    queue<string> toProcess;
    map<string, Gate> gateMap;
    readProgram(DATA_PATH + "p24.txt", toProcess, gateMap);

    bool converted = true;
    set<string> swapped;
    while (converted) {
        converted = false;

        for (auto& [k, g] : gateMap) {
            if (g.type == INITIAL) {
                if (k[0] == 'z' && g.name[0] != '$') {
                    int b = stoi(k.substr(1));
                    for (auto& [ok, og] : gateMap) {
                        if (og.name == ("$" + to_string(b))) {
                            swapped.insert(g.key);
                            swapped.insert(og.key);
                            print("swap", g.key, og.key);
                            swap(g, og);
                            converted = true;
                            break;
                        }
                    }
                }
                continue;
            };
            if (gateMap[g.input1].type > gateMap[g.input2].type || (gateMap[g.input1].type == gateMap[g.input2].type && gateMap[g.input1].name < gateMap[g.input2].name)) {
                swap(g.input1, g.input2);
            }
            auto& g1 = gateMap[g.input1];
            auto& g2 = gateMap[g.input2];
            if (g.input1[0] == 'x' || g.input1[0] == 'y') {
                if (g.type == AND) g.name = "&";
                else if (g.type == OR) g.name = "|";
                else if (g.type == XOR) g.name = "^";
                g.name += to_string(stoi(g.input1.substr(1)));
                if (g.name == "&0") g.name = "_0";
                g.type = INITIAL;
                converted = true;
                continue;
            }
            else if (g.type == AND && g1.name[0] == '_') {
                int b = stoi(g1.name.substr(1));
                if (g2.name == ("^" + to_string(b + 1))) {
                    g.name = "!" + to_string(b + 2);
                    g.type = INITIAL;
                    converted = true;
                }
            }
            else if (g.type == OR && g2.name[0] == '!') {
                int b = stoi(g2.name.substr(1));
                if (g1.name == ("&" + to_string(b - 1))) {
                    g.name = "_" + to_string(b - 1);
                    g.type = INITIAL;
                    converted = true;
                }
            }
            else if (g.type == XOR && g1.name[0] == '_') {
                int b = stoi(g1.name.substr(1));
                if (g2.name == ("^" + to_string(b + 1))) {
                    g.name = "$" + to_string(b + 1);
                    g.type = INITIAL;
                    converted = true;
                }
                else if (g.name[0] == 'z') {
                    if (g2.name != ("^" + to_string(b + 1))) {
                        for (auto& [ok, og] : gateMap) {
                            if (og.name == ("^" + to_string(b + 1))) {
                                print("swap", g2.key, og.key);
                                swapped.insert(g2.key);
                                swapped.insert(og.key);
                                swap(g2, og);
                                converted = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 46; ++i) {
        vector<string> list;
        string gate = "z" + string(i < 10 ? "0" : "") + to_string(i);
        getDeps(gateMap, list, gate);
        print(i, list);
    }
    string str;
    string sep;
    for (const auto& g : swapped) {
        str += sep + g;
        sep = ",";
    }
    print(str);
}
}

void p24() {
    p24_1();
    p24_2();
}
