#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

size_t p2(std::vector<std::string> &as) {
        if (as.size() == 1) {
                return as[0].length();
        }

        std::unordered_map<char, size_t> acount{};
        for (auto &a : as) {
                for (auto &c : a) {
                        auto it = acount.find(c);
                        if (it != acount.end()) {
                                it->second++;
                                continue;
                        }

                        acount.insert({c, 0});
                }
        }

        return std::ranges::count_if(
                acount.begin(), acount.end(),
                [&](const auto &e) { return e.second + 1 == as.size(); });
}

size_t p1(std::vector<std::string> &as) {
        std::unordered_set<char> aunion{};

        for (auto &a : as) {
                for (auto &c : a) {
                        aunion.insert(c);
                }
        }

        return aunion.size();
}

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<std::string> ass{};
        auto sum = 0;

        for (std::string line; std::getline(input, line);) {
                if (line == "") {
                        sum += p2(ass);

                        ass.clear();
                        continue;
                }

                ass.push_back(line);
        }

        sum += p2(ass);

        std::cout << sum << std::endl;
}
