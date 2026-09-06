#include "Position.h"
#include "Pieces.h"
#include <vector>
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Piece &obj){
    os << obj.get_color() << obj.get_symbol() << "\033[0m";
    return os;
}