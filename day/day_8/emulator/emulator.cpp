#include "emulator.hpp"

constexpr auto log_vector = [](const int64_t &a) { std::cout << a; };

void Instruction::log() {
        std::cout << std::left << std::setw(10);
        auto str_in = Instruction::string_from(Instruction::opcode);
        std::cout << std::setw(10) << str_in;
        std::cout << std::setw(10) << rd;
        std::cout << std::setw(10) << rs1;
        std::cout << std::setw(10) << rs2;

        std::cout << std::endl;
}

std::string Instruction::get_opcode_string() { return string_from(opcode); }

errcode Instruction::set_opcode_from(std::string &string) {
        opcode = opcode_from(string);
        return errcode::ok;
};

errcode Instruction::execute(size_t &pc, std::vector<int64_t> &registers) {
        switch (opcode) {
        case opcode_t::no_op:
                pc++;
                return errcode::ok;
        case opcode_t::acc:
                registers[0] += rs1;
                pc++;
                return errcode::ok;
        case opcode_t::jmp:
                pc = pc + rs1;
                return errcode::ok;
        default:
                return errcode::not_implemented;
        }

        return errcode::ok;
}

void Emulator::log() {
        std::cout << std::left << std::setw(10) << pc;
        std::for_each(registers.begin(), registers.end(), log_vector);
        std::cout << std::endl;
}

std::vector<Instruction> &Emulator::access_code() { return code; }

Instruction &Emulator::access_instruction(size_t pc) { return code[pc]; };

std::pair<int64_t, errcode> Emulator::access_register(const std::string &key) {
        if (key == "acc") {
                return {registers[0], errcode::ok};
        }

        return {0, errcode::not_implemented};
}

errcode Emulator::load_instruction(Instruction &in) {
        if (mode & 1)
                in.log();

        code.push_back(in);

        return errcode::ok;
}

errcode Emulator::Restart() {
        pc = 0;
        registers[0] = 0;
        instructions_cache.clear();
        return errcode::ok;
}

errcode Emulator::Start() {
        auto err = errcode::ok;
        for (; pc < code.size();) {
                auto it = instructions_cache.find(pc);
                if (it != instructions_cache.end()) {
                        return errcode::infinite_loop;
                }

                instructions_cache.insert({pc, 1});
                err = code[pc].execute(pc, registers);
        }

        return err;
}
