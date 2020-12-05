#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

constexpr auto cmp = [](const size_t &a, const size_t &b) {
        return std::abs((long double)a) < std::abs((long double)b);
};

constexpr auto find_gap = [](const size_t &a, const size_t &b) {
        return (b - a) == 2;
};

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<size_t> ids{};

        for (std::string line; std::getline(input, line);) {
                size_t i = 0, lo = 0, row = 0;
                for (auto j = 128; j >>= 1;) {
                        if (line[i++] == 'B') {
                                lo += j;
                        }
                }

                row = lo, lo = 0;
                for (auto j = 8; j >>= 1;) {
                        if (line[i++] == 'R') {
                                lo += j;
                        }
                }

                ids.push_back((row * 8) + lo);
        }

        auto highest_id = std::max_element(ids.begin(), ids.end(), cmp);

        std::cout << *highest_id << std::endl;

        std::sort(ids.begin(), ids.end(), cmp);

        auto after = std::adjacent_find(ids.begin(), ids.end(), find_gap);

        std::cout << (*after) + 1 << std::endl;
}
