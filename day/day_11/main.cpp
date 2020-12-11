#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

constexpr char empty = 'L';
constexpr char busy = '#';
constexpr char floor = '.';
constexpr char outside = ' ';

enum direction { n, nw, w, sw, s, se, e, ne };

auto directions = {direction::n, direction::nw, direction::w, direction::sw,
                   direction::s, direction::se, direction::e, direction::ne};

std::vector<std::string> dstr{"north", "north-west", "west", "south-west",
                              "south", "south-east", "east", "north-east"};

std::vector<int64_t> dis{-1, -1, 0, 1, 1, 1, 0, -1};

std::vector<int64_t> djs{0, -1, -1, -1, 0, 1, 1, 1};

constexpr auto debug = false;

/* for part 1 check in radius 1, instead of until set != floor */
constexpr auto seat_at_dir = [](const auto &g, const auto &d, auto i, auto j) {
        char seat;
        if (debug)
                std::cout << dstr[d] << " ";
        try {
                switch (d) {
                case direction::n: {
                        do {
                                seat = g.at(i - 1).at(j);
                                i--;
                        } while (seat == floor);
                        return seat;
                }
                case direction::nw: {
                        do {
                                seat = g.at(i - 1).at(j - 1);
                                i--;
                                j--;
                        } while (seat == floor);
                        return seat;
                }
                case direction::w: {
                        do {
                                seat = g.at(i).at(j - 1);
                                j--;
                        } while (seat == floor);
                        return seat;
                }
                case direction::sw: {
                        do {
                                seat = g.at(i + 1).at(j - 1);
                                j--;
                                i++;
                        } while (seat == floor);
                        return seat;
                }
                case direction::s: {
                        do {
                                seat = g.at(i + 1).at(j);
                                i++;
                        } while (seat == floor);
                        return seat;
                }
                case direction::se: {
                        do {
                                seat = g.at(i + 1).at(j + 1);
                                i++;
                                j++;
                        } while (seat == floor);
                        return seat;
                }
                case direction::e: {
                        do {
                                seat = g.at(i).at(j + 1);
                                j++;
                        } while (seat == floor);
                        return seat;
                }
                case direction::ne: {
                        do {
                                seat = g.at(i - 1).at(j + 1);
                                j++;
                                i--;
                        } while (seat == floor);
                        return seat;
                }
                }
        } catch (const std::out_of_range &e) {
                return outside;
        }
};

bool tick(std::vector<std::string> &grid, const auto &tolerance) {
        std::vector<std::string> ngrid(grid.size());
        std::copy(grid.begin(), grid.end(), ngrid.begin());

        bool changed = false;

        for (size_t i = 0; i < grid.size(); i++) {
                auto row = grid[i];

                for (size_t j = 0; j < row.length(); j++) {
                        auto seat = grid[i][j];

                        if (seat == floor)
                                continue;

                        auto occupied = 0;
                        for (const auto &d : directions) {
                                auto seat = seat_at_dir(grid, d, i, j);

                                occupied += seat == busy ? 1 : 0;
                        }

                        if (seat == empty && occupied == 0)
                                ngrid[i][j] = busy, changed = true;
                        else if (seat == busy && occupied >= tolerance)
                                ngrid[i][j] = empty, changed = true;
                }
        }

        grid = ngrid;

        return changed;
}

int main(int argc, char **argv) {
        std::fstream in(*++argv);
        if (!in) {
                exit(1);
        }

        std::vector<std::string> grid{};
        for (std::string line; std::getline(in, line);) {
                grid.push_back(line);
        }

        in.close();

        auto tolerance = 4;

        size_t occupied = 0;

        /*
        // part 1
        while (tick(grid, tolerance))
                ;

        for (auto &row : grid) {
                for (auto &s : row) {
                        occupied += s == busy ? 1 : 0;
                }
        }

        std::cout << "p1: " << occupied << std::endl;
        */

        tolerance = 5;
        occupied = 0;

        while (tick(grid, tolerance))
                ;

        for (auto &row : grid) {
                for (auto &s : row) {
                        occupied += s == busy ? 1 : 0;
                }
        }

        std::cout << "p2: " << occupied << std::endl;
}
