#include <iostream>
#include "Board.h"
#include "Functions.h"
#include "Pieces.h"
#include "Position.h"
#include <vector>
#include <algorithm>
Board::Board()
    :board{
        // Row 0 (y=0): Black major pieces
        { new Rook{"black", {0,0}},   new Horse{"black", {1,0}}, new Bishop{"black", {2,0}}, new Queen{"black", {3,0}}, 
          new King{"black", {4,0}},   new Bishop{"black", {5,0}}, new Horse{"black", {6,0}}, new Rook{"black", {7,0}} },
        
        // Row 1 (y=1): Black pawns
        { new Pawn{"black", {0,1}},   new Pawn{"black", {1,1}},   new Pawn{"black", {2,1}},   new Pawn{"black", {3,1}}, 
          new Pawn{"black", {4,1}},   new Pawn{"black", {5,1}},   new Pawn{"black", {6,1}},   new Pawn{"black", {7,1}} },

        // Row 2 (y=2): Empty squares
        { new Piece{{0,2}}, new Piece{{1,2}}, new Piece{{2,2}}, new Piece{{3,2}}, 
          new Piece{{4,2}}, new Piece{{5,2}}, new Piece{{6,2}}, new Piece{{7,2}} },

        // Row 3 (y=3): Empty squares
        { new Piece{{0,3}}, new Piece{{1,3}}, new Piece{{2,3}}, new Piece{{3,3}}, 
          new Piece{{4,3}}, new Piece{{5,3}}, new Piece{{6,3}}, new Piece{{7,3}} },

        // Row 4 (y=4): Empty squares
        { new Piece{{0,4}}, new Piece{{1,4}}, new Piece{{2,4}}, new Piece{{3,4}}, 
          new Piece{{4,4}}, new Piece{{5,4}}, new Piece{{6,4}}, new Piece{{7,4}} },

        // Row 5 (y=5): Empty squares
        { new Piece{{0,5}}, new Piece{{1,5}}, new Piece{{2,5}}, new Piece{{3,5}}, 
          new Piece{{4,5}}, new Piece{{5,5}}, new Piece{{6,5}}, new Piece{{7,5}} },

        // Row 6 (y=6): White pawns
        { new Pawn{"white", {0,6}},   new Pawn{"white", {1,6}},   new Pawn{"white", {2,6}},   new Pawn{"white", {3,6}}, 
          new Pawn{"white", {4,6}},   new Pawn{"white", {5,6}},   new Pawn{"white", {6,6}},   new Pawn{"white", {7,6}} },

        // Row 7 (y=7): White major pieces
        { new Rook{"white", {0,7}},   new Horse{"white", {1,7}}, new Bishop{"white", {2,7}}, new Queen{"white", {3,7}}, 
          new King{"white", {4,7}},   new Bishop{"white", {5,7}}, new Horse{"white", {6,7}}, new Rook{"white", {7,7}} }
    }{}

Board::Board(Piece *p){
    //initializing 
    for (int i = 0; i < 8; i++) {
        std::vector<Piece *> row;
        for (int j = 0; j < 8; j++) {
            row.push_back(new Piece{{j, i}});
        }
        board.push_back(row);
    }

    position pos = p->get_position();
    if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8) {
        delete board[pos.y][pos.x];
        board[pos.y][pos.x] = p;
    } else {
        delete p;
        display_message("Error: Position out of bounds. Piece not placed.");
    }
}

Board::Board(std::vector<Piece *> ps){
    //initializing 
    for (int i = 0; i < 8; i++) {
        std::vector<Piece *> row;
        for (int j = 0; j < 8; j++) {
            row.push_back(new Piece{{j, i}});
        }
        board.push_back(row);
    }

    for (auto p : ps) {
        position pos = p->get_position();
        if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8) {
            delete board[pos.y][pos.x];
            board[pos.y][pos.x] = p;
        } else {
            delete p;
            display_message("Error: Position out of bounds. Piece not selected.");
        }
    }
}

Board::~Board(){
    for (auto &i : board) {
        for (auto &j : i) {
            delete j; // Free the memory allocated for each Piece
        }
    }
}

void Board::print_board() const {
    std::cout << "\033[2J\033[1;1H"; //clear screen and move to top left
    for (auto i : board){
        std::cout << "-------------------------" << std::endl;
        for (auto j : i)
            std::cout << "|" << *j << " ";
        std::cout << "|" << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

void Board::select_piece(position pos) {
    if(turn == board.at(pos.y).at(pos.x)->get_color_string() && selected_piece.x == -1 && selected_piece.y == -1){
        if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8) {
            std::vector<position> valid_moves = board.at(pos.y).at(pos.x)->determinemovement(board);
            if (valid_moves.empty()) {
                display_message("No valid moves for this piece.");
            } else {
                selected_piece.x = pos.x;
                selected_piece.y = pos.y;
                for(auto pos : valid_moves){
                    if (board.at(pos.y).at(pos.x)->get_symbol() == " ") {
                        std::cout << "\033[s\033[" << pos.y * 2 + 2 << ";" << pos.x * 3 + 2 << "H" << "\033[42m" << "  " << "\033[0m\033[u"; // set valid move grounds that there is not an enemy piece in them to green then restore cursor position
                    }
                    else if (board.at(pos.y).at(pos.x)->get_color_string() != turn) {
                        std::cout << "\033[s\033[" << pos.y * 2 + 2 << ";" << pos.x * 3 + 2 << "H" << "\033[41m" << board.at(pos.y).at(pos.x)->get_symbol() << "\033[0m\033[u"; // set valid move grounds that there is an enemy piece in them to red then restore cursor position
                    }
                }
            }
        } else {
            display_message("Error: Position out of bounds.");
        }
    }
    else if (turn != board.at(pos.y).at(pos.x)->get_color_string() && selected_piece.x == -1 && selected_piece.y == -1){
        display_message("not your turn bro / not your piece bro");
    }
    else if (selected_piece.x != -1 && selected_piece.y != -1){
        bool flag=false;
        std::vector<position> valid_moves = board.at(selected_piece.y).at(selected_piece.x)->determinemovement(board);
        for (auto p : valid_moves){
            if (p.x == pos.x && p.y == pos.y){
                flag=true;
                break;
            }
        }
        if (!flag) {
            selected_piece.x = -1;
            selected_piece.y = -1;
            print_board();
            select_piece(pos);
        }else{
            if(move_piece(selected_piece, pos)){
                selected_piece.x = -1;
                selected_piece.y = -1;
                print_board();
                turn = (turn == "white") ? "black" : "white";
                turn_incheck=is_incheck(turn);
                if (turn_incheck)
                    display_message("CHECK!");
            }
            else{
                print_board();
                display_message("there is a check present");
            }
        }
    }
    
}

bool Board::move_piece(position from, position to){
    Piece *moving_piece = board.at(from.y).at(from.x);
    Piece *target_piece = board.at(to.y).at(to.x);
    Piece *temp=board.at(to.y).at(to.x);
    // if (board.at(from.y).at(from.x)->get_symbol() == "♟" && board.at(to.y).at(to.x)->get_symbol() == " " && abs(from.x-to.x) == 1){
    //     delete board.at(from.y).at(to.x);
    //     board.at(from.y).at(to.x) = new Piece{{to.x, from.y}};
    // }
    board.at(to.y).at(to.x) = board.at(from.y).at(from.x);
    board.at(from.y).at(from.x) = new Piece{{from.x, from.y}};
    board.at(to.y).at(to.x)->set_position(to);
    if (is_incheck(turn)){
        delete board.at(from.y).at(from.x);
        board.at(from.y).at(from.x) = board.at(to.y).at(to.x);
        board.at(to.y).at(to.x) = temp;
        board.at(from.y).at(from.x)->set_position(from);
        return false;
    }
    else{
        delete temp;
        board.at(to.y).at(to.x)->set_position(to);
        return true;
    }
}

bool Board::can_move(position from, position to){
    Piece *moving_piece = board.at(from.y).at(from.x);
    Piece *target_piece = board.at(to.y).at(to.x);
    Piece *temp=board.at(to.y).at(to.x);
    // if (board.at(from.y).at(from.x)->get_symbol() == "♟" && board.at(to.y).at(to.x)->get_symbol() == " " && abs(from.x-to.x) == 1){
    //     delete board.at(from.y).at(to.x);
    //     board.at(from.y).at(to.x) = new Piece{{to.x, from.y}};
    // }
    board.at(to.y).at(to.x) = board.at(from.y).at(from.x);
    board.at(from.y).at(from.x) = new Piece{{from.x, from.y}};
    board.at(to.y).at(to.x)->set_position(to);
    if (is_incheck(turn)){
        delete board.at(from.y).at(from.x);
        board.at(from.y).at(from.x) = board.at(to.y).at(to.x);
        board.at(to.y).at(to.x) = temp;
        board.at(from.y).at(from.x)->set_position(from);
        return false;
    }
    else{
        delete board.at(from.y).at(from.x);
        board.at(from.y).at(from.x) = board.at(to.y).at(to.x);
        board.at(to.y).at(to.x) = temp;
        board.at(from.y).at(from.x)->set_position(from);
        return true;
    }
}

void Board::display_message(const std::string &message) const {
    std::cout << "\033[s" << "\033[9;30H" <<message << "\033[u" << std::endl; // save position then printout message then restore position
}

bool Board::is_incheck(std::string color_name){
    for (auto& i : board)
        for (auto& j : i){
            if (j->get_symbol() == "♚" && color_name==j->get_color_string()){
                std::vector<position> cant_move{illegal_moves_for_king(color_name)};
                if(std::find(cant_move.begin(), cant_move.end(), j->get_position()) == cant_move.end()){
                    return false;
                }
                else return true;
            }
        }
    std::cerr << "welp";
    return true;
}

std::vector<position> Board::illegal_moves_for_king(std::string color_name){
    std::vector<position> cant_move{};
    std::vector<position> cant_move_append{};
    for (auto& i : board)
        for (auto& j : i){
            if (j->get_color_string() != color_name){    
                if (j->get_symbol() == "♚"){
                    position pk = j->get_position();
                    cant_move_append={{pk.x-1, pk.y-1}, {pk.x, pk.y-1}, {pk.x+1, pk.y-1}, {pk.x-1, pk.y}, {pk.x+1, pk.y}, {pk.x-1, pk.y+1}, {pk.x, pk.y+1}, {pk.x+1, pk.y+1}};
                }
                else if(j->get_symbol() == "♟"){
                    position pp = j->get_position();
                    if (color_name == "white"){
                        cant_move_append={{pp.x-1,pp.y+1},{pp.x+1,pp.y+1}};
                    }
                    else if (color_name == "black"){
                        cant_move_append={{pp.x-1,pp.y-1},{pp.x+1,pp.y-1}};
                    }
                }
                else{
                    cant_move_append=j->determinemovement(board);
                }
                for (const auto& move : cant_move_append)
                    if(std::find(cant_move.begin(), cant_move.end(), move) == cant_move.end())
                        cant_move.push_back(move);
            }
            else if (j->get_color_string() == color_name && j->get_symbol() != "♚"){
                if(std::find(cant_move.begin(), cant_move.end(), j->get_position()) == cant_move.end())
                        cant_move.push_back(j->get_position());
            }
        }
    return cant_move;
}

bool Board::is_game_over(){
    for (auto& i : board)
        for (auto& j : i){
            if(j == nullptr){
                std::cerr << "wha";
                continue;
            }
            if(j->get_color_string() != turn)
                continue;
            std::vector<position> moveset;
            position my_pos{j->get_position()};
            moveset=j->determinemovement(board);
            for (auto& k: moveset){
                if(can_move(my_pos, k))
                    return false;
            }
        }
    return true;
}