#include <iostream>
#include <map>
#include <vector>

#include "util.h"

using namespace std;

namespace {
void p19_1() {
    struct p19_1_impl {
        vector<string> available;
        map<string, bool> mem;

        bool possible(const string& str) {
            if (str.empty()) return true;
            auto it = mem.find(str);
            if (it != mem.end()) return it->second;
            bool p = false;
            for (const auto& a : available) {
                size_t i = 0;
                for (; i < a.size() && i < str.size(); ++i) {
                    if (a[i] != str[i]) break;
                }
                if (i == a.size() && possible(str.substr(a.size()))) {
                    p = true;
                    break;
                }
            }
            mem[str] = p;
            return p;
        }
        void run() {
            auto data = readFile(DATA_PATH + "p19.txt");
            available = splitString(data[0], ',');
            for (auto& a : available) if (a[0] == ' ') a = a.substr(1);
            int count = 0;
            for (size_t i = 2; i < data.size(); ++i) {
                count += possible(data[i]);
            }
            print(count);
        }
    };
    p19_1_impl().run();
}

void p19_2() {
    struct p19_2_impl {
        vector<string> available;
        map<string, int64_t> mem;

        int64_t counts(const string& str) {
            if (str.empty()) return 1;
            auto it = mem.find(str);
            if (it != mem.end()) return it->second;
            int64_t c = 0;
            for (const auto& a : available) {
                size_t i = 0;
                for (; i < a.size() && i < str.size(); ++i) {
                    if (a[i] != str[i]) break;
                }
                if (i == a.size()) {
                    c += counts(str.substr(a.size()));
                }
            }
            mem[str] = c;
            return c;
        }
        void run() {
            auto data = readFile(DATA_PATH + "p19.txt");
            available = splitString(data[0], ',');
            for (auto& a : available) if (a[0] == ' ') a = a.substr(1);
            int64_t count = 0;
            for (size_t i = 2; i < data.size(); ++i) {
                count += counts(data[i]);
            }
            print(count);
        }
    };
    p19_2_impl().run();
}
}

void p19() {
    p19_1();
    p19_2();
}
