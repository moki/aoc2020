#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

constexpr auto cmp = [](const auto &a, const auto &b) { return a < b; };

constexpr auto find_gap = [](const auto &a, const auto &b) {
        return (b - a) == 2;
};

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<size_t> ids{};

        for (std::string line; std::getline(input, line);) {
                auto id = 0;
                for (auto j = 1 << 10, i = 0; j >>= 1; i++) {
                        id |= (line[i] == 'B' || line[i] == 'R') ? j : 0;
                }

                ids.push_back(id);
        }

        std::sort(ids.begin(), ids.end(), cmp);

        std::cout << ids[ids.size() - 1] << std::endl;

        auto after = std::adjacent_find(ids.begin(), ids.end(), find_gap);

        std::cout << (*after) + 1 << std::endl;
}
