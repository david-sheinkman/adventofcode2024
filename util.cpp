#include "util.h"

#include <fstream>
#include <regex>
#include <sstream>

std::vector<std::string> readFile(const std::string& path) {
	std::ifstream is(path);

	std::vector<std::string> result;
	for (std::string str; std::getline(is, str);) {
		result.emplace_back(str);
	}

	return result;
}

std::vector<std::string> splitString(const std::string& str, const char c, const bool allowEmpty) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	for (std::string s; std::getline(ss, s, c);) {
		if (allowEmpty || !s.empty()) result.emplace_back(s);
	}
	return result;
}

std::vector<int64_t> stringToInt64Vec(const std::vector<std::string>& vec) {
	std::vector<int64_t> newVec;
	for (const auto& s : vec) {
		newVec.emplace_back(stoll(s));
	}
	return newVec;
}

std::vector<int64_t> extractInts(const std::string& str, const std::string& regex) {
	std::vector<int64_t> result;

	std::regex r(regex);
	std::smatch sm;

	if (std::regex_search(str, sm, r)) {
		for (size_t i = 1; i < sm.size(); i++) {
			result.emplace_back(stoll(sm[i]));
		}
	}

	return result;
}
