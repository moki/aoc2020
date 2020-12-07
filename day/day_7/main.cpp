#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

typedef std::pair<std::string, size_t> bag;

constexpr char *delimeter = const_cast<char *>(" bag");

std::vector<bag>
parse_rule(std::string & line) {
        size_t pos = 0;
        bool first = true;

        std::vector<bag> bags{};

        while ((pos = line.find(delimeter)) != std::string::npos) {
                auto rule = line.substr(0, pos);
                line = line.substr(pos);

                size_t amount = 1;
                if (isdigit(rule[0])) {
                        auto pos_num_end = rule.find(" ");
                        amount = std::stoi(rule.substr(0, pos_num_end));
                        rule = rule.substr(pos_num_end + 1);
                }

                bags.push_back({rule, amount});

                for (pos = 0; line[pos] && !isdigit(line[pos]); pos++)
                        ;
                line = line.substr(pos);
        }

        return bags;
}

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<std::string> ass{};
        auto sum = 0;
        std::unordered_map<std::string, std::vector<bag>> paths{};

        for (std::string line; std::getline(input, line);) {
                auto bags = parse_rule(line);

                auto it = bags.begin();
                auto key = (*it).first;

                bags.erase(it);

                paths.insert({key, std::move(bags)});
        }

        auto lookup_bag = "shiny gold";
        auto found = 0;

        for (auto &path : paths) {
                std::deque<bag> stack(path.second.begin(), path.second.end());

                while (!stack.empty()) {
                        auto item = stack.back();

                        if (item.first == lookup_bag) {
                                found++;
                                break;
                        }

                        stack.pop_back();

                        auto lookup_path = paths.find(item.first);
                        if (lookup_path != paths.end()) {
                                stack.insert(stack.end(),
                                             lookup_path->second.begin(),
                                             lookup_path->second.end());
                        }
                }
        }

        std::cout << "part 1: " << found << std::endl;

        found = 0;
        auto shiny_path = paths.find(lookup_bag);
        std::deque<bag> stack(shiny_path->second.begin(),
                              shiny_path->second.end());

        while (!stack.empty()) {
                auto item = stack.back();
                stack.pop_back();

                auto path = paths.find(item.first);
                if (path == paths.end())
                        break;

                auto depth = item.second;
                while (depth--) {
                        found++;
                        stack.insert(stack.end(), path->second.begin(),
                                     path->second.end());
                }
        }

        std::cout << "part 2: " << found << std::endl;
}
