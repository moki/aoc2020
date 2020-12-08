#include "emulator/emulator.hpp"
#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

constexpr char *delimeter = const_cast<char *>(" ");

Instruction parse_instruction(std::string &line) {
        std::vector<int64_t> args(1);
        std::string in;

        bool in_args = false;
        size_t pos = 0, i = 0;

        while ((pos = line.find(delimeter)) != std::string::npos) {
                auto token = line.substr(0, pos);
                line = line.substr(pos + 1);

                if (in_args) {
                        args[i++] = std::stoi(token);
                        continue;
                }

                in = std::move(token);
                in_args = true;
        }

        args[i] = std::stoi(line);
        auto instruction = Instruction(in, 0, args[i], 0);

        return instruction;
}

int main(int argc, char **argv) {
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        auto flags = 0;
        auto emu = Emulator(flags);
        errcode err;

        std::vector<size_t> problematic{};
        auto jmp = "jmp"s;
        auto nop = "nop"s;
        size_t pc = 0;

        for (std::string line; std::getline(input, line);) {
                auto in = parse_instruction(line);

                err = emu.load_instruction(in);
                if (err != errcode::ok) {
                        std::cerr << "emulator error loading instruction"
                                  << std::endl;
                        exit(1);
                }

                auto opcode = in.get_opcode_string();
                if (opcode == jmp || opcode == nop)
                        problematic.push_back(pc);
                pc++;
        }

        for (auto &pc : problematic) {
                auto op = emu.access_instruction(pc).get_opcode_string();
                err = emu.access_instruction(pc).set_opcode_from(
                        op == "jmp" ? nop : jmp);
                if (err != errcode::ok) {
                        std::cerr << "emulator error loading instruction"
                                  << std::endl;
                        exit(1);
                }

                err = emu.Start();
                if (err == errcode::ok) {
                        break;
                }

                op = emu.access_instruction(pc).get_opcode_string();
                err = emu.access_instruction(pc).set_opcode_from(
                        op == "jmp" ? nop : jmp);
                if (err != errcode::ok) {
                        std::cerr << "emulator error loading instruction"
                                  << std::endl;
                        exit(1);
                }

                err = emu.Restart();
        }

        auto acc = emu.access_register("acc");
        if (acc.second == errcode::ok)
                std::cout << "acc: " << acc.first << std::endl;
}
