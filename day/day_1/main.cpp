#include <fstream>
#include <iostream>
#include <vector>

int main() {
        std::fstream input("input");
        if (!input) {
                exit(1);
        }

        uint32_t n;
        std::vector<uint32_t> ns{};

        for (; input >> n;) {
                ns.push_back(n);
        }

        /* part 1 */
        for (auto i = ns.begin(); i != ns.end(); i++) {
                for (auto j = i + 1; j != ns.end(); j++) {
                        if (*i + *j == 2020) {
                                std::cout << *i * *j << std::endl;
                        }
                }
        }

        /* part 2 lazy to hashmap sums, godbless moores law */
        for (auto i = ns.begin(); i != ns.end(); i++) {
                for (auto j = i + 1; j != ns.end(); j++) {
                        for (auto k = j + 1; k != ns.end(); k++) {
                                if (*i + *j + *k == 2020) {
                                        std::cout << *i * *j * *k << std::endl;
                                }
                        }
                }
        }
}
