#include <iostream>
#include "Board.h"
#include "Functions.h"
#include "Pieces.h"
#include "Position.h"
#include <vector>
#include <algorithm>
#include <memory>
#include "exceptions-chess.h"
#include "Input.h"

Board::Board()
        : board(8){
        for (int x = 0; x < 8; ++x) {
            std::unique_ptr<Piece> black_major;
            if (x == 0 || x == 7) black_major = std::make_unique<Rook>("black", position{x, 0});
            else if (x == 1 || x == 6) black_major = std::make_unique<Horse>("black", position{x, 0});
            else if (x == 2 || x == 5) black_major = std::make_unique<Bishop>("black", position{x, 0});
            else if (x == 3) black_major = std::make_unique<Queen>("black", position{x, 0});
            else black_major = std::make_unique<King>("black", position{x, 0});
            board[0].push_back(std::move(black_major));
                board[1].push_back(std::make_unique<Pawn>("black", position{x, 1}));
                for (int y = 2; y <= 5; ++y)
                        board[y].push_back(std::make_unique<Piece>(position{x, y}));
                board[6].push_back(std::make_unique<Pawn>("white", position{x, 6}));
                std::unique_ptr<Piece> white_major;
                if (x == 0 || x == 7) white_major = std::make_unique<Rook>("white", position{x, 7});
                else if (x == 1 || x == 6) white_major = std::make_unique<Horse>("white", position{x, 7});
                else if (x == 2 || x == 5) white_major = std::make_unique<Bishop>("white", position{x, 7});
                else if (x == 3) white_major = std::make_unique<Queen>("white", position{x, 7});
                else white_major = std::make_unique<King>("white", position{x, 7});
                board[7].push_back(std::move(white_major));
        }
}

Board::Board(std::unique_ptr<Piece> p){
    //initializing 
    for (int i = 0; i < 8; i++) {
        std::vector<std::unique_ptr<Piece>> row;
        for (int j = 0; j < 8; j++) {
            row.push_back(std::make_unique<Piece>(position{j, i}));
        }
        board.push_back(std::move(row));
    }

    position pos = p->get_position();
    if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8) {
        board[pos.y][pos.x] = std::move(p);
    } else {
        display_message("Error: Position out of bounds. Piece not placed.");
    }
}

Board::Board(std::vector<std::unique_ptr<Piece>> ps){
    //initializing 
    for (int i = 0; i < 8; i++) {
        std::vector<std::unique_ptr<Piece>> row;
        for (int j = 0; j < 8; j++) {
            row.push_back(std::make_unique<Piece>(position{j, i}));
        }
        board.push_back(std::move(row));
    }

    for (auto& p : ps) {
        position pos = p->get_position();
        if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8) {
            board[pos.y][pos.x] = std::move(p);
        } else {
            display_message("Error: Position out of bounds. Piece not selected.");
        }
    }
}

void Board::start_game_simulation() {
    print_board();
    Input inp{{3,16}};
    while (!is_game_over()) {
        display_message(turn + "'s turn. Select a piece to move                                     ");
        bool flag = false;
        while (!flag) {
            try {
                select_piece(inp.get_input_keyboard());
                flag = true;
            } catch (const IllegalMoveException& e) {
                display_message(e.what());
            }
        }
    }
    print_board();
    if (is_incheck(turn)){
        turn_change();
        display_message("Check Mate! " + turn + " wins!");
    } else display_message("Stale Mate!");
}

void Board::print_board() const {
    std::cout << "\033[2J\033[1;1H"; //clear screen and move to top left
    for (const auto& i : board){
        std::cout << "-------------------------" << std::endl;
        for (const auto& j : i)
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
                throw IllegalMoveException("no valid moves for selected piece");
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
            throw IllegalMoveException("Position out of bounds.");
        }
    }
    else if (turn != board.at(pos.y).at(pos.x)->get_color_string() && selected_piece.x == -1 && selected_piece.y == -1){
        throw IllegalMoveException("not your turn / not your piece");
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
                turn_change();
                turn_incheck=is_incheck(turn);
                if (turn_incheck)
                    display_message("CHECK!");
            }
            else{
                print_board();
                throw IllegalMoveException("your king is in check");
            }
        }
    }
}

bool Board::move_piece(position from, position to){
    auto moving_piece = std::move(board.at(from.y).at(from.x));
    auto captured_piece = std::move(board.at(to.y).at(to.x));
    // if (board.at(from.y).at(from.x)->get_symbol() == "♟" && board.at(to.y).at(to.x)->get_symbol() == " " && abs(from.x-to.x) == 1){
    //     delete board.at(from.y).at(to.x);
    //     board.at(from.y).at(to.x) = new Piece{{to.x, from.y}};
    // }
    board.at(to.y).at(to.x) = std::move(moving_piece);
    board.at(from.y).at(from.x) = std::make_unique<Piece>(position{from.x, from.y});
    board.at(to.y).at(to.x)->set_position(to);
    if (is_incheck(turn)){
        moving_piece = std::move(board.at(to.y).at(to.x));
        board.at(from.y).at(from.x) = std::move(moving_piece);
        board.at(to.y).at(to.x) = std::move(captured_piece);
        board.at(from.y).at(from.x)->set_position(from);
        return false;
    }
    else{
        board.at(to.y).at(to.x)->set_position(to);
        return true;
    }
}

bool Board::can_move(position from, position to){
    auto moving_piece = std::move(board.at(from.y).at(from.x));
    auto captured_piece = std::move(board.at(to.y).at(to.x));
    // if (board.at(from.y).at(from.x)->get_symbol() == "♟" && board.at(to.y).at(to.x)->get_symbol() == " " && abs(from.x-to.x) == 1){
    //     delete board.at(from.y).at(to.x);
    //     board.at(from.y).at(to.x) = new Piece{{to.x, from.y}};
    // }
    board.at(to.y).at(to.x) = std::move(moving_piece);
    board.at(from.y).at(from.x) = std::make_unique<Piece>(position{from.x, from.y});
    board.at(to.y).at(to.x)->set_position(to);
    if (is_incheck(turn)){
        moving_piece = std::move(board.at(to.y).at(to.x));
        board.at(from.y).at(from.x) = std::move(moving_piece);
        board.at(to.y).at(to.x) = std::move(captured_piece);
        board.at(from.y).at(from.x)->set_position(from);
        return false;
    }
    else{
        moving_piece = std::move(board.at(to.y).at(to.x));
        board.at(from.y).at(from.x) = std::move(moving_piece);
        board.at(to.y).at(to.x) = std::move(captured_piece);
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