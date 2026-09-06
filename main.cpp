#include <iostream>
#include <vector>
#include "Position.h"
#include "Pieces.h"
#include "Functions.h"
#include "Board.h"
#include "Input.h"

//♚ ♛ ♜ ♝ ♞ ♟

int main(){
    Board board{};
    board.start_game_simulation();
    return 0;
}