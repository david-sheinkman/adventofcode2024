#include <iostream>
#include <vector>

#include "util.h"

using namespace std;

namespace {
string runProgram(vector<int64_t> registers, const vector<int64_t>& program) {
    vector<int64_t> output;
    auto opValue = [&](int64_t v) {
        if (v >= 4 && v <= 6) return registers[v - 4];
        return v;
    };
    size_t ip = 0;
    while (ip < program.size()) {
        int64_t ins = program[ip++];
        int64_t op = program[ip++];
        int64_t opCombo = opValue(op);
        switch (ins) {
        case 0:
            registers[0] = registers[0] / (1ll << opCombo);
            break;
        case 1:
            registers[1] = registers[1] ^ op;
            break;
        case 2:
            registers[1] = opCombo % 8;
            break;
        case 3:
            if (registers[0] != 0) ip = op;
            break;
        case 4:
            registers[1] = registers[1] ^ registers[2];
            break;
        case 5:
            output.emplace_back(opCombo % 8);
            break;
        case 6:
            registers[1] = registers[0] / (1ll << opCombo);
            break;
        case 7:
            registers[2] = registers[0] / (1ll << opCombo);
            break;
        }
    }
    string out;
    for (auto o : output) out += to_string(o);
    return out;
}
void p17_1() {
    auto data = readFile(DATA_PATH + "p17.txt");
    vector<int64_t> registers(3);

    registers[0] = extractInts(data[0], ".*: (-?[0-9]*)")[0];
    registers[1] = extractInts(data[1], ".*: (-?[0-9]*)")[0];
    registers[2] = extractInts(data[2], ".*: (-?[0-9]*)")[0];
    vector<int64_t> program;
    for (const auto& s : splitString(data[4].substr(9), ',')) {
        program.emplace_back(stoll(s));
    }
    print(runProgram(registers, program));
}
void reverse(string& str) {
    for (int i = 0; i < str.size() / 2; ++i) {
        swap(str[i], str[str.size() - 1 - i]);
    }
}

void p17_2() {
    auto data = readFile(DATA_PATH + "p17.txt");
    vector<int64_t> registers(3);

    registers[0] = 0;
    registers[1] = extractInts(data[1], ".*: (-?[0-9]*)")[0];
    registers[2] = extractInts(data[2], ".*: (-?[0-9]*)")[0];
    vector<int64_t> program;
    string str;
    for (const auto& s : splitString(data[4].substr(9), ',')) {
        str += s;
        program.emplace_back(stoll(s));
    }
    if (true) {
        int64_t p = 1ll << (program.size() - 1);
        registers[0] += p * p * p;
        for (int i = static_cast<int>(program.size()) - 1; i > 1; --i) {
            int64_t p = 1ll << (i);
            p *= p * p;
            auto out = runProgram(registers, program);
            while ((out[i] - '0') != program[i]) {
                if (i == 0) registers[0]--;
                else registers[0] += p;
                out = runProgram(registers, program);
            }
        }
        auto out = runProgram(registers, program);
        while (out != str) {
            ++registers[0];
            out = runProgram(registers, program);
        }
        print(registers[0]);
        return;
    }
    /*
    char prev='a';
    for (int i = 0; true; ++i) {
        const int L = 6;
        registers[0] = i;
        auto out = runProgram(registers, program);
        if (out.length() == L) {
            if (prev != out[L - 2]) print(i, out, out[L - 2]);
            prev = out[L - 2];
        }
        else if (out.length() > L) break;
    }
    */
}
}

void p17() {
    p17_1();
    p17_2();
}
