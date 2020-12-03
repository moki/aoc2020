#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

size_t p1(std::vector<std::string> &grid, size_t dx, size_t dy) {
        size_t s = 0;

        for (size_t y = 0, x = 0; y < grid.size();
             x = (x + dx) % grid[y].length(), y = y + dy) {
                if (grid[y][x] == '#')
                        s++;
        }

        return s;
}

int main(int argc, char **argv) {
        std::ios_base::sync_with_stdio(false);
        std::fstream input(*++argv);
        if (!input) {
                exit(1);
        }

        size_t solution = 0;

        std::vector<std::string> grid{};

        for (std::string line; std::getline(input, line);) {
                grid.push_back(line);
        }

        solution = p1(grid, 3, 1);

        std::cout << solution << std::endl;

        std::cout << solution * p1(grid, 1, 1) * p1(grid, 5, 1) *
                             p1(grid, 7, 1) * p1(grid, 1, 2)
                  << std::endl;
}
