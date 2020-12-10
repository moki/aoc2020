#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<size_t> seq{};
        std::unordered_map<size_t, size_t> diff{};

        seq.push_back(0);

        for (std::string line; std::getline(input, line);) {
                seq.push_back(std::stoll(line));
        }

        input.close();

        std::sort(seq.begin(), seq.end());
        seq.push_back(seq[seq.size() - 1] + 3);

        for (auto i = seq.begin(), j = i + 1; j != seq.end(); i++, j++) {
                auto it = diff.find(*j - *i);
                if (it != diff.end()) {
                        it->second++;
                        continue;
                }

                diff.insert({(*j) - (*i), 1});
        }

        auto p1 = diff.find(1)->second * diff.find(3)->second;

        std::cout << "p1: " << p1 << std::endl;

        std::vector<size_t> memo(seq.size());

        /*
         * memo[x] += memo[x-1] + memo[x-2] + memo[x-3];
         */

        memo[0] = 1;
        memo[1] = (seq[1] - seq[0] <= 3 ? 1 : 0);
        memo[2] = (seq[2] - seq[1] <= 3 ? 1 : 0) + memo[1];

        size_t j = 3;
        for (auto i = seq.begin() + 3; i != seq.end(); i++, j++) {
                if ((*i - *(i - 1)) <= 3) {
                        memo[j] = memo[j - 1];
                }
                if ((*i - *(i - 2)) <= 3) {
                        memo[j] += memo[j - 2];
                }
                if ((*i - *(i - 3)) <= 3) {
                        memo[j] += memo[j - 3];
                }
        }

        std::cout << "p2: " << memo[memo.size() - 1] << std::endl;
}
