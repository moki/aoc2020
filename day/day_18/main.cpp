#include <bits/stdc++.h>

constexpr char lparen = '(';
constexpr char rparen = ')';
constexpr char mul = '*';
constexpr char add = '+';

void parse_into_postfix(std::string &expression, std::deque<char> &output,
                        std::deque<char> &operators,
                        std::unordered_map<char, size_t> &precedence) {

        operators.clear();
        output.clear();

        for (auto &token : expression) {
                switch (token) {
                case lparen: {
                        operators.push_back(token);
                        break;
                }
                case rparen: {
                        char next;
                        while (operators.size()) {
                                next = operators.back();
                                if (next == lparen) {
                                        break;
                                }

                                operators.pop_back();
                                output.push_back(next);
                        }

                        if (next && next == lparen)
                                operators.pop_back();
                        break;
                }
                case mul: {
                }
                case add: {
                        while (operators.size()) {
                                char next = operators.back();
                                if (next == lparen)
                                        break;

                                auto npit = precedence.find(next);
                                if (npit == precedence.end())
                                        exit(0);
                                auto cpit = precedence.find(token);
                                if (cpit == precedence.end())
                                        exit(0);

                                if (npit->second < cpit->second)
                                        break;

                                output.push_back(next);
                                operators.pop_back();
                        }

                        operators.push_back(token);
                        break;
                }
                case ' ': {
                        break;
                }
                default: {
                        output.push_back(token);
                }
                }
        }

        while (operators.size()) {
                auto op = operators.back();
                operators.pop_back();

                output.push_back(op);
        }
}

void evaluate_postfix(std::deque<char> &expression,
                      std::deque<size_t> &output) {

        output.clear();

        for (auto &token : expression) {
                if (token != mul && token != add) {
                        output.push_back(token - '0');
                        continue;
                }

                auto a = output.back();
                output.pop_back();
                auto b = output.back();
                output.pop_back();

                auto c = token == mul ? (a * b) : (a + b);

                output.push_back(c);
        }
}

void solution(auto &in) {
        std::string line;

        std::deque<char> output{};
        std::deque<char> operators{};
        std::unordered_map<char, size_t> precedence{{mul, 1}, {add, 2}};

        std::deque<size_t> eval_stack{};

        size_t sum = 0;

        for (; std::getline(in, line);) {
                parse_into_postfix(line, output, operators, precedence);

                evaluate_postfix(output, eval_stack);

                sum += eval_stack.back();
        }

        std::cout << sum << std::endl;

        in.close();
}

int main(int argc, char **argv) {
        std::fstream in(*++argv);
        if (!in) {
                exit(1);
        }

        solution(in);
}
