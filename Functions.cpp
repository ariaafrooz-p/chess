#include "Position.h"
#include "Pieces.h"
#include <vector>
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Piece &obj){
    os << obj.get_color() << obj.get_symbol() << "\033[0m";
    return os;
}

// void print_board(const std::vector<std::vector<Piece *>> &board){
//     for (auto i : board){
//         std::cout << "-------------------------" << std::endl;
//         for (auto j : i)
//             std::cout << "|" << *j << " ";
//         std::cout << "|" << std::endl;
//     }
//     std::cout << "-------------------------" << std::endl;
// }