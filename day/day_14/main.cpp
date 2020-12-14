#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

/* disclaimer: ugliest shiet u've ever seen */

constexpr char space = ' ';

void p1(auto &in) {
        std::unordered_map<size_t, size_t> mem{};

        std::string mask;

        size_t pos;
        std::string token;

        for (std::string line; std::getline(in, line);) {
                pos = line.find(space);
                token = line.substr(0, pos);

                if (token == "mask") {
                        line = line.substr(pos + 1);
                        pos = line.find(space);
                        mask = line.substr(pos + 1);
                        continue;
                }

                auto left = token.find('[') + 1;
                auto right = token.find(']');

                auto address = token.substr(left, right - left);

                line = line.substr(pos + 3);

                size_t value = std::stoll(line);

                size_t bit_pos = 35;
                for (auto &c : mask) {
                        if (c == '1') {
                                value |= 1ULL << bit_pos;
                        }
                        if (c == '0') {
                                value &= ~(1ULL << bit_pos);
                        }
                        bit_pos--;
                }

                mem[std::stoll(address)] = std::move(value);
        }

        in.close();

        size_t sum = 0;
        for (auto &m : mem) {
                sum += m.second;
        }

        std::cout << sum << std::endl;
}

void p2(auto &in) {
        std::unordered_map<size_t, size_t> mem{};
        std::string mask;

        size_t pos;
        std::string token;

        for (std::string line; std::getline(in, line);) {
                pos = line.find(space);
                token = line.substr(0, pos);

                if (token == "mask") {
                        line = line.substr(pos + 1);
                        pos = line.find(space);
                        mask = line.substr(pos + 1);
                        continue;
                }

                auto left = token.find('[') + 1;
                auto right = token.find(']');

                auto address = std::stoll(token.substr(left, right - left));

                line = line.substr(pos + 3);

                size_t value = std::stoll(line);

                std::vector<size_t> floating_bits{};

                size_t bit_pos = 35;
                for (auto &c : mask) {
                        if (c == '1') {
                                address |= 1ULL << bit_pos;
                        }
                        if (c == 'X') {
                                floating_bits.push_back(bit_pos);
                        }
                        bit_pos--;
                }

                std::vector<size_t> memory_addresses{};

                std::string universe{};
                universe.insert(0, floating_bits.size(), '0');

                for (size_t k = 0; k <= universe.size(); k++) {
                        universe[universe.size() - k] = '1';

                        do {
                                auto floating_address = address;

                                for (size_t j = 0; j < floating_bits.size();
                                     j++) {
                                        if (universe[j] == '1')
                                                floating_address |=
                                                        1ULL
                                                        << floating_bits[j];
                                        if (universe[j] == '0')
                                                floating_address &=
                                                        ~(1ULL
                                                          << floating_bits[j]);
                                }

                                mem[floating_address] = value;
                        } while (std::next_permutation(universe.begin(),
                                                       universe.end()));
                }
        }

        in.close();

        size_t sum = 0;
        for (auto &m : mem) {
                sum += m.second;
        }

        std::cout << sum << std::endl;
}

int main(int argc, char **argv) {
        std::fstream in(*++argv);
        if (!in) {
                exit(1);
        }

        // p1(in);
        p2(in);
}
