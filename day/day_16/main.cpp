#include <bits/stdc++.h>

void solution(auto &in) {
        std::unordered_set<size_t> allowed{};
        std::unordered_map<std::string, std::unordered_set<size_t>>
                field_to_rules{};
        std::vector<std::vector<size_t>> valid_tickets{};

        bool parsing_rules = true;
        size_t i = 0;
        size_t errcode = 0;

        for (std::string line; std::getline(in, line);) {
                if (!line.length()) {
                        parsing_rules = false;
                        continue;
                }

                auto kvsep = line.find(':');
                auto key = line.substr(0, kvsep);
                std::unordered_set<size_t> rules{};

                if (!parsing_rules)
                        goto parsing_tickets;

                line = line.substr(kvsep + 2);

                for (size_t pos = 0;
                     (pos = line.find('-')) != std::string::npos;) {

                        auto lo = std::stoll(line.substr(0, pos));

                        auto hi = std::stoll(
                                line.substr(pos + 1, line.find(' ') - pos - 1));

                        std::vector<size_t> range(hi - lo + 1);

                        std::iota(range.begin(), range.end(), lo);

                        std::copy(range.begin(), range.end(),
                                  std::inserter(allowed, allowed.end()));

                        std::copy(range.begin(), range.end(),
                                  std::inserter(rules, rules.end()));

                        auto sepidx = line.find("or");
                        if (sepidx == std::string::npos)
                                break;

                        line = line.substr(sepidx + 3);
                }

                field_to_rules.insert({key, rules});

                continue;

        parsing_tickets:
                if (!line.length())
                        continue;
                if (line == "your ticket:")
                        continue;
                if (line == "nearby tickets:")
                        continue;

                std::vector<size_t> ticket_numeric{};
                std::string token;
                size_t pos = 0;
                auto ticket = line;
                bool valid_ticket = true;

                for (; (pos = line.find(',')) != std::string::npos;) {
                        token = line.substr(0, pos);

                        auto number = std::stoll(token);
                        ticket_numeric.push_back(number);
                        if (!allowed.contains(number)) {
                                errcode += number;
                                valid_ticket = false;
                        }

                        line = line.substr(pos + 1);
                }

                auto number = std::stoll(line);
                ticket_numeric.push_back(number);
                if (!allowed.contains(number)) {
                        errcode += number;
                        valid_ticket = false;
                }

                if (valid_ticket) {
                        valid_tickets.push_back(ticket_numeric);
                }
        }

        in.close();

        std::cout << errcode << std::endl;

        auto ticket_length = valid_tickets[0].size();

        std::vector<std::vector<std::string>> idx_to_field(ticket_length);

        for (auto &i : idx_to_field) {
                i = std::vector<std::string>{};
        }

        std::unordered_set<size_t> idx_to_skip{};
        std::unordered_set<std::string> field_to_skip{};

        for (size_t j = 0; j < ticket_length; j++) {

                idx_to_field =
                        std::vector<std::vector<std::string>>(ticket_length);

                for (auto &rule : field_to_rules) {
                        if (field_to_skip.contains(rule.first))
                                continue;
                        for (size_t i = 0; i < ticket_length; i++) {
                                /*
                                if (idx_to_skip.contains(i))
                                        continue;
                                */

                                bool col_valid = true;

                                for (auto &ticket : valid_tickets) {
                                        auto number = ticket[i];
                                        col_valid =
                                                col_valid &&
                                                rule.second.contains(number);
                                }

                                if (col_valid) {
                                        idx_to_field[i].push_back(rule.first);
                                }
                        }
                }

                for (size_t i = 0; i < ticket_length; i++) {
                        if (idx_to_field[i].size() == 1) {
                                field_to_skip.insert(idx_to_field[i][0]);
                                idx_to_skip.insert(i);
                        }
                }
        }

        auto colw = 20;

        std::cout << std::left;

        for (auto &i : idx_to_skip)
                std::cout << std::setw(colw) << i;
        std::cout << std::endl;

        for (auto &f : field_to_skip)
                std::cout << std::setw(colw) << f;
        std::cout << std::endl;

        for (size_t i = 0; i < ticket_length; i++)
                std::cout << std::setw(colw) << valid_tickets[0][i];

        std::cout << std::endl;
        std::cout << std::endl;

        for (auto &f : field_to_skip)
                std::cout << std::setw(colw) << f;
        std::cout << std::endl;

        auto iit = idx_to_skip.begin();
        auto fit = field_to_skip.begin();
        for (size_t i = 0; i < ticket_length; i++) {
                auto index = *(iit);
                auto field = *(fit);

                std::cout << std::setw(colw) << valid_tickets[0][index];

                iit++;
                fit++;
        }
        std::cout << std::endl;
}

int main(int argc, char **argv) {
        std::fstream in(*++argv);
        if (!in) {
                exit(1);
        }

        solution(in);
}
