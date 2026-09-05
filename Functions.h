#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include <vector>
#include "Pieces.h"

void print_board(const std::vector<std::vector<Piece *>> &board);

std::ostream &operator<<(std::ostream &os, const Piece &obj);

#endif