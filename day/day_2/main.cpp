#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<std::string> solutions{};

        for (int i = 0; !input.eof(); i++) {
                int64_t low, high;
                input >> low >> high;
                high *= -1;

                char token;
                input >> token;
                input.ignore(std::numeric_limits<std::streamsize>::max(), ':');

                std::string pw;

                input >> pw;

                if (!pw.length())
                        continue;

                /* part one */
                std::unordered_map<char, uint32_t> compressed{};

                for (auto &c : pw) {
                        auto lookup = compressed.find(c);
                        if (lookup != compressed.end()) {
                                lookup->second++;
                        } else {
                                compressed.insert({c, 1});
                        }
                }

                /*
                auto occured = compressed.find(token);
                if (occured != compressed.end() && occured->second <= high &&
                    occured->second >= low) {
                        solutions.push_back(pw);
                }
                */

                /* part two */
                if ((pw[low - 1] != token) != (pw[high - 1] != token)) {
                        solutions.push_back(pw);
                }
        }

        std::cout << solutions.size() << std::endl;
}
