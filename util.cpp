#include "util.h"

#include <sstream>
#include <fstream>

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
