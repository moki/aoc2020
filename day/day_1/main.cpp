#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std::chrono;

uint64_t sliding_pointer_part1(const std::vector<uint64_t> &ns,
                               uint64_t target) {
        for (auto i = ns.begin(); i != ns.end(); i++) {
                for (auto j = i + 1, k = ns.end() - 1; j < k;) {
                        auto mid = (j + (k - j) / 2);
                        auto sum = *i + *mid;

                        if (sum == target) {
                                std::cout << "pair: (" << *i << ", " << *mid
                                          << ")" << std::endl;

                                return *i * *mid;
                        }

                        if (sum < target) {
                                j = mid + 1;
                        } else {
                                k = mid - 1;
                        }
                }
        }

        return 0;
}

uint64_t sliding_pointer_part2(std::vector<uint64_t> &ns, uint64_t target) {
        for (auto i = ns.begin(); i != ns.end(); i++) {
                for (auto j = i + 1, k = ns.end() - 1; j < k;) {
                        auto sum = *i + *j + *k;
                        if (sum == target) {
                                std::cout << "triplet: (" << *i << ", " << *j
                                          << ", " << *k << ")" << std::endl;
                                return *i * *j * *k;
                        }

                        if (sum < target) {
                                j++;
                        } else {
                                k--;
                        }
                }
        }

        return 0;
}

constexpr uint64_t t = 2020;

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        uint64_t n;
        std::vector<uint64_t> ns{};

        for (; input >> n;) {
                ns.push_back(n);
        }

        std::sort(ns.begin(), ns.end());

        // part 1
        auto before = std::chrono::high_resolution_clock::now();
        auto solution = sliding_pointer_part1(ns, t);
        auto after = std::chrono::high_resolution_clock::now();

        auto took = duration_cast<microseconds>(after - before);
        std::cout << "bsearch part 1 solution: " << took.count() << "μs"
                  << std::endl;

        std::cout << "solution: " << solution << std::endl;

        // part 2
        before = std::chrono::high_resolution_clock::now();
        solution = sliding_pointer_part2(ns, t);
        after = std::chrono::high_resolution_clock::now();

        took = duration_cast<microseconds>(after - before);
        std::cout << "sliding window part 2 solution: " << took.count() << "μs"
                  << std::endl;

        std::cout << "solution: " << solution << std::endl;
}
