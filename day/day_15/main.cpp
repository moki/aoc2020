#include <bits/stdc++.h>

/* disclaimer: ugliest shiet u've ever seen */

void solution(auto &in, auto &limit) {
        std::unordered_map<size_t, std::deque<size_t>> numbers{};

        size_t pos = 0, i = 1;

        std::string line;
        std::string token;
        std::getline(in, line);

        std::vector<size_t> seed{};

        for (; (pos = line.find(',')) != std::string::npos;) {
                token = line.substr(0, pos);
                line = line.substr(pos + 1);

                seed.push_back(std::stoll(token));

                numbers.insert({std::stoll(token), std::deque<size_t>{i}});

                i++;
        }

        in.close();

        numbers.insert({std::stoll(line), std::deque<size_t>{i}});
        size_t last_number = std::stoll(line);
        i++;

        for (; i <= limit;) {
                auto it = numbers.find(last_number);
                auto times_spoken = it->second.size();

                last_number = 0;

                if (times_spoken > 1) {
                        auto last = it->second.back();
                        it->second.pop_back();

                        auto second_last = it->second.back();
                        it->second.pop_back();

                        it->second.push_back(last);

                        last_number = last - second_last;
                }

                auto yit = numbers.find(last_number);
                if (yit == numbers.end()) {
                        numbers.insert({last_number, std::deque<size_t>{i}});
                } else {
                        yit->second.push_back({i});
                }

                i++;
        }

        std::cout << last_number << std::endl;
}

int main(int argc, char **argv) {
        std::fstream in(*++argv);
        if (!in) {
                exit(1);
        }

        auto p1 = 2020;
        auto p2 = 30000000;

        // p1(in, p1);

        solution(in, p2);
}
