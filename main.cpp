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
    board.print_board();
    Input inp{{3,2}};
    bool flag=false;
    while (!flag)
    {
        board.select_piece(inp.get_input_keyboard());
        flag=board.is_game_over();
    }

    if (board.is_incheck(board.get_turn()))
        board.display_message("Check Mate!");
    else board.display_message("Stale Mate!");

    return 0;
}