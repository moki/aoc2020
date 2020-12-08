#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>

enum class errcode { ok, not_implemented, infinite_loop };

using namespace std::string_literals;

class Instruction {
        public:
                Instruction(std::string &op): opcode{opcode_from(op)}, rd{}, rs1{}, rs2{} {};
                Instruction(std::string &op, int64_t rd, int64_t rs1, int64_t rs2): opcode{opcode_from(op)}, rd{rd}, rs1{rs1}, rs2{rs2} {};
                std::string get_opcode_string();
                errcode set_opcode_from(std::string &string);
                void log();
                errcode execute(size_t &pc, std::vector<int64_t> &registers);
        private:
                enum class opcode_t { no_op, acc, jmp };

                opcode_t opcode_from(std::string &s) {
                        if (s == "nop") {
                                return opcode_t::no_op;
                        } else if (s == "acc") {
                                return opcode_t::acc;
                        } else if (s == "jmp") {
                                return opcode_t::jmp;
                        } else {
                                exit(1);
                        }
                }

                std::string string_from(opcode_t &opcode) {
                        switch(opcode) {
                                case opcode_t::no_op:
                                        return "nop";
                                        break;
                                case opcode_t::acc:
                                        return "acc";
                                        break;
                                case opcode_t::jmp:
                                        return "jmp";
                                        break;
                                default:
                                        exit(1);
                        }
                }

                opcode_t opcode;
                int64_t rd;
                int64_t rs1;
                int64_t rs2;
};

class Emulator {
        public:
                Emulator(): pc{0}, registers(1), mode{0}{};
                Emulator(uint8_t flags): pc{0}, registers(1), mode{flags}{};
                std::pair<int64_t, errcode> access_register(const std::string &key);
                std::vector<Instruction> &access_code();

                errcode load_instruction(Instruction &in);
                Instruction &access_instruction(size_t at);
                errcode Start();
                errcode Restart();
        private:
                void log();
                // registers
                // 0: acc
                size_t pc;
                uint8_t mode;
                std::vector<Instruction> code;
                std::vector<int64_t> registers;
                std::unordered_map<size_t, int64_t> instructions_cache;
};
