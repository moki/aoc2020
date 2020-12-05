#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include <algorithm>
#include <cctype>
#include <locale>

#include <stdlib.h>

// trim from start (in place)
static inline void ltrim(std::string &s) {
        s.erase(s.begin(),
                std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                        return !std::isspace(ch);
                }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); })
                        .base(),
                s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
}

size_t valid_passwords_count = 0;

void read_passport(std::vector<std::string> &lines, size_t from, size_t to) {
        auto pairs = 0;
        bool seen_cid = false;
        bool valid_fields = true;

        for (; from < to; from++) {
                std::string line = lines[from];

                std::string key, val;

                size_t pos_del, pos_start = 0;

                while ((pos_del = line.find(':')) != std::string::npos) {
                        key = line.substr(pos_start, pos_del);
                        if (key == "cid")
                                seen_cid = true;

                        line = line.substr(pos_del + 1);

                        pos_del = line.find(' ');
                        if (pos_del == std::string::npos)
                                pos_del = line.length() - 1;
                        val = line.substr(pos_start, pos_del + 1);

                        std::cout << "key: " << key << " val: " << val
                                  << std::endl;

                        if (key == "byr") {
                                auto year = trim_copy(val);
                                auto value = std::stoi(year);
                                valid_fields = valid_fields &&
                                               year.length() == 4 &&
                                               (value >= 1920 && value <= 2002);
                        }

                        if (key == "iyr") {
                                auto year = trim_copy(val);
                                auto value = std::stoi(year);
                                valid_fields = valid_fields &&
                                               year.length() == 4 &&
                                               (value >= 2010 && value <= 2020);
                        }

                        if (key == "eyr") {
                                auto year = trim_copy(val);
                                auto value = std::stoi(year);
                                valid_fields = valid_fields &&
                                               year.length() == 4 &&
                                               (value >= 2020 && value <= 2030);
                        }

                        if (key == "hgt") {
                                auto height = trim_copy(val);
                                auto unit = height.substr(height.length() - 2);
                                auto value =
                                        height.substr(0, height.length() - 2);

                                if (unit == "in") {
                                        auto _value = std::stoi(value);
                                        valid_fields =
                                                valid_fields &&
                                                (_value >= 59 && _value <= 76);
                                } else if (unit == "cm") {
                                        auto _value = std::stoi(value);
                                        valid_fields = valid_fields &&
                                                       (_value >= 150 &&
                                                        _value <= 193);
                                } else {
                                        valid_fields = false;
                                }
                        }

                        if (key == "hcl") {
                                auto color = trim_copy(val);
                                auto prefix = color.substr(0, 1);
                                std::cout << "prefix: " << prefix << std::endl;
                                auto value = color.substr(1);
                                if (prefix == "#") {
                                        auto _value = std::strtoul(
                                                value.c_str(), NULL, 16);
                                        valid_fields = valid_fields &&
                                                       _value != ERANGE &&
                                                       _value != EINVAL;
                                } else {
                                        valid_fields = false;
                                }
                        }

                        if (key == "ecl") {
                                auto value = trim_copy(val);
                                valid_fields =
                                        valid_fields &&
                                        (value == "amb" || value == "blu" ||
                                         value == "brn" || value == "gry" ||
                                         value == "grn" || value == "hzl" ||
                                         value == "oth");
                        }

                        if (key == "pid") {
                                auto value = trim_copy(val);
                                auto _value =
                                        std::strtoul(value.c_str(), NULL, 0);
                                valid_fields =
                                        valid_fields && value.length() == 9 &&
                                        _value != ERANGE && _value != EINVAL;
                        }

                        line = line.substr(pos_del + 1);
                        pairs++;
                }
        }

        std::cout << "pairs: " << pairs << std::endl;
        std::cout << "valid: " << valid_fields << std::endl;

        if ((pairs == 8 || (pairs == 7 && !seen_cid)) && valid_fields) {
                valid_passwords_count++;
        }
}

int main(int argc, char **argv) {
        std::ios_base::sync_with_stdio(false);
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        std::vector<std::string> lines{};

        auto n = 0;
        auto i = 0;
        auto from = 0;
        auto to = 0;

        for (std::string line; std::getline(input, line);) {
                n++;
                i++;

                if (line == "") {
                        from = i - n;
                        to = from + (n - 1);
                        read_passport(lines, from, to);
                        n = 0;
                }

                lines.push_back(line);
        }

        from = to;
        to = lines.size();

        read_passport(lines, from, to);

        std::cout << valid_passwords_count << std::endl;
}
