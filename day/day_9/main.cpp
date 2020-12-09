#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

constexpr size_t ring_size = 25;

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<size_t> ring(ring_size);
        std::vector<size_t> seq{};

        bool seeding = true;
        size_t i = 0, j = 0;
        size_t invalid;

        for (std::string line; std::getline(input, line);) {
                invalid = std::stoll(line);
                seq.push_back(invalid);
                bool found_sum = false;
                j = i + 1;

                if (seeding) {
                        ring[i] = invalid;
                        seeding = j != ring_size;
                        goto after_seeding;
                }

                for (auto k = ring.begin(); k != ring.end(); k++) {
                        for (auto l = k + 1; l != ring.end(); l++) {
                                if (*l + *k == invalid) {
                                        ring[i] = invalid;
                                        found_sum = true;
                                        goto next;
                                }
                        }
                }
        next:
                if (!found_sum && !seeding) {
                        std::cout << "p1: " << invalid << std::endl;

                        break;
                }
        after_seeding:
                i = j % ring_size;
        }

        for (auto i = seq.begin(); i != seq.end(); i++) {
                size_t sum = invalid - *i;
                for (auto j = i + 1; j != seq.end(); j++) {
                        sum -= *j;
                        if (sum == 0) {
                                auto min = std::min_element(i, j);
                                auto max = std::max_element(i, j);
                                std::cout << "p2: " << *min + *max << std::endl;
                                return 0;
                        }
                }
        }
}
