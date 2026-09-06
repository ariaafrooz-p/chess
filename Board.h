#ifndef _BOARD_H_
#define _BOARD_H_
#include "Pieces.h"
#include <vector>
#include <memory>

class Board{
private:
    position selected_piece{-1,-1};
    std::string turn="white";
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    bool turn_incheck=false;

public:
    Board();
    Board(std::unique_ptr<Piece> p);
    Board(std::vector<std::unique_ptr<Piece>> ps);
    ~Board() = default;
    void start_game_simulation();
    bool move_piece(position from, position to);
    void print_board() const;
    bool select_piece(position pos);
    void turn_change() {turn = (turn == "white") ? "black" : "white";}
    void display_message(const std::string &message) const;
    bool is_incheck(std::string color_name);
    std::vector<position> illegal_moves_for_king(std::string color_name);
    bool can_move(position from, position to);
    bool is_game_over();
    std::string get_turn() {return turn;}
};

#endif