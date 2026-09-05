#include "Pieces.h"
#include "Position.h"
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<position> Piece::determinemovement(const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    return {};
}
std::vector<position> Rook::determinemovement(const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> moves;
    int difference=0;
    bool blocked_up=false, blocked_down=false, blocked_left=false, blocked_right=false;
    while (difference<7){
        difference++;
        if (pos.y-difference>=0 && !blocked_up){
            if (board.at(pos.y-difference).at(pos.x)->get_symbol()==" "){
                moves.push_back({pos.x, pos.y-difference});
            }
            else{
                blocked_up=true;
                if (board.at(pos.y-difference).at(pos.x)->get_color()!=displaycolor)
                    moves.push_back({pos.x, pos.y-difference});
            }
        }
        if (pos.y+difference<=7 && !blocked_down){
            if (board.at(pos.y+difference).at(pos.x)->get_symbol()==" "){
                moves.push_back({pos.x, pos.y+difference});
            }
            else{
                blocked_down=true;
                if (board.at(pos.y+difference).at(pos.x)->get_color()!=displaycolor)
                    moves.push_back({pos.x, pos.y+difference});
            }
        }
        if (pos.x-difference>=0 && !blocked_left){
            if (board.at(pos.y).at(pos.x-difference)->get_symbol()==" "){
                moves.push_back({pos.x-difference, pos.y});
            }
            else{
                blocked_left=true;
                if (board.at(pos.y).at(pos.x-difference)->get_color()!=displaycolor)
                    moves.push_back({pos.x-difference, pos.y});
            }
        }
        if (pos.x+difference<=7 && !blocked_right){
            if (board.at(pos.y).at(pos.x+difference)->get_symbol()==" "){
                moves.push_back({pos.x+difference, pos.y});
            }
            else{
                blocked_right=true;
                if (board.at(pos.y).at(pos.x+difference)->get_color()!=displaycolor)
                    moves.push_back({pos.x+difference, pos.y});
            }
        }
    }
    return moves;
}

std::vector<position> Bishop::determinemovement(const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> moves;
    int difference=0;
    bool blocked_up_left=false, blocked_up_right=false, blocked_down_left=false, blocked_down_right=false;
    while (difference<7){
        difference++;
        if (pos.y-difference>=0 && pos.x-difference>=0 && !blocked_up_left){
            if (board.at(pos.y-difference).at(pos.x-difference)->get_symbol()==" "){
                moves.push_back({pos.x-difference, pos.y-difference});
            }
            else{
                blocked_up_left=true;
                if (board.at(pos.y-difference).at(pos.x-difference)->get_color()!=displaycolor)
                    moves.push_back({pos.x-difference, pos.y-difference});
            }
        }
        if (pos.y-difference>=0 && pos.x+difference<=7 && !blocked_up_right){
            if (board.at(pos.y-difference).at(pos.x+difference)->get_symbol()==" "){
                moves.push_back({pos.x+difference, pos.y-difference});
            }
            else{
                blocked_up_right=true;
                if (board.at(pos.y-difference).at(pos.x+difference)->get_color()!=displaycolor)
                    moves.push_back({pos.x+difference, pos.y-difference});
            }
        }
        if (pos.y+difference<=7 && pos.x-difference>=0 && !blocked_down_left){
            if (board.at(pos.y+difference).at(pos.x-difference)->get_symbol()==" "){
                moves.push_back({pos.x-difference, pos.y+difference});
            }
            else{
                blocked_down_left=true;
                if (board.at(pos.y+difference).at(pos.x-difference)->get_color()!=displaycolor)
                    moves.push_back({pos.x-difference, pos.y+difference});
            }
        }
        if (pos.y+difference<=7 && pos.x+difference<=7 && !blocked_down_right){
            if (board.at(pos.y+difference).at(pos.x+difference)->get_symbol()==" "){
                moves.push_back({pos.x+difference, pos.y+difference});
            }
            else{
                blocked_down_right=true;
                if (board.at(pos.y+difference).at(pos.x+difference)->get_color()!=displaycolor)
                    moves.push_back({pos.x+difference, pos.y+difference});
            }
        }
    }
    return moves;
}

std::vector<position> Horse::determinemovement (const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> moves;
    std::vector<position> potential_moves = {
        {pos.x + 2, pos.y + 1}, {pos.x + 2, pos.y - 1},
        {pos.x - 2, pos.y + 1}, {pos.x - 2, pos.y - 1},
        {pos.x + 1, pos.y + 2}, {pos.x + 1, pos.y - 2},
        {pos.x - 1, pos.y + 2}, {pos.x - 1, pos.y - 2}
    };
    for (auto p : potential_moves) {
        if (p.x >= 0 && p.x < 8 && p.y >= 0 && p.y < 8 && (board.at(p.y).at(p.x)->get_symbol() == " " || board.at(p.y).at(p.x)->get_color() != displaycolor)) {
            moves.push_back(p);
        }
    }
    return moves;
}

std::vector<position> Queen::determinemovement(const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> moves {Rook::determinemovement(board)};
    std::vector<position> bishop_moves {Bishop::determinemovement(board)};
    moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
    return moves;
}

std::vector<position> King::illegal_moves_for_king(const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> cant_move{};
    std::vector<position> cant_move_append{};
    std::string color_name = get_color_string();
    for (const auto& i : board)
        for (const auto& j : i){
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
            else if (j->get_color_string() == color_name){
                if(std::find(cant_move.begin(), cant_move.end(), j->get_position()) == cant_move.end())
                        cant_move.push_back(j->get_position());
            }
        }
    return cant_move;
}

std::vector<position> King::determinemovement(const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> moves {{pos.x-1, pos.y-1}, {pos.x, pos.y-1}, {pos.x+1, pos.y-1}, {pos.x-1, pos.y}, {pos.x+1, pos.y}, {pos.x-1, pos.y+1}, {pos.x, pos.y+1}, {pos.x+1, pos.y+1}};
    std::vector<position> cant_move{illegal_moves_for_king(board)};
    for (int i=moves.size()-1; i>=0; i--)
        if (std::find(cant_move.begin(), cant_move.end(), moves[i]) != cant_move.end())
            moves.erase(moves.begin() + i);
    for (int i=moves.size()-1; i>=0; i--)
        if(moves[i].x < 0 || moves[i].x > 7 || moves[i].y < 0 || moves[i].y > 7)
            moves.erase(moves.begin() + i);
    return moves;
}

std::vector<position> Pawn::determinemovement (const std::vector<std::vector<std::unique_ptr<Piece>>> &board){
    std::vector<position> moves;
    int y_move_value=0;
    std::string my_color{get_color_string()};
    if(my_color=="white")
        y_move_value=-1;
    else 
        y_move_value=1;
    if (board.at(pos.y+y_move_value).at(pos.x)->get_symbol() == " ")
        moves.push_back({pos.x, pos.y+y_move_value});
    if (my_color=="white" && pos.y==6 && board.at(pos.y+y_move_value).at(pos.x)->get_symbol() == " " && board.at(pos.y-2).at(pos.x)->get_symbol() == " ")
        moves.push_back({pos.x, pos.y-2});
    if (my_color=="black" && pos.y==1 && board.at(pos.y+y_move_value).at(pos.x)->get_symbol() == " " && board.at(pos.y+2).at(pos.x)->get_symbol() == " ")
        moves.push_back({pos.x, pos.y+2});
    if (pos.x>0){
        if (board.at(pos.y+y_move_value).at(pos.x-1)->get_color_string() != my_color && board.at(pos.y+y_move_value).at(pos.x-1)->get_color_string() != "yellow")
            moves.push_back({pos.x-1, pos.y+y_move_value});
        if (pos.y == 3 && my_color == "white" && board.at(pos.y).at(pos.x-1)->get_symbol() == "♟" && board.at(pos.y).at(pos.x-1)->has_just_moved_2_spaces)
            moves.push_back({pos.x-1, pos.y+1});
        if (pos.y == 4 && my_color == "black" && board.at(pos.y).at(pos.x-1)->get_symbol() == "♟" && board.at(pos.y).at(pos.x-1)->has_just_moved_2_spaces)
            moves.push_back({pos.x-1, pos.y-1});
    }
    if (pos.x<7){
        if (board.at(pos.y+y_move_value).at(pos.x+1)->get_color_string() != my_color && board.at(pos.y+y_move_value).at(pos.x+1)->get_color_string() != "yellow")
            moves.push_back({pos.x+1, pos.y+y_move_value});
        if (pos.y == 3 && my_color == "white" && board.at(pos.y).at(pos.x+1)->get_symbol() == "♟" && board.at(pos.y).at(pos.x+1)->has_just_moved_2_spaces)
            moves.push_back({pos.x+1, pos.y+1});
        if (pos.y == 4 && my_color == "black" && board.at(pos.y).at(pos.x+1)->get_symbol() == "♟" && board.at(pos.y).at(pos.x+1)->has_just_moved_2_spaces)
            moves.push_back({pos.x+1, pos.y-1});
    }
    return moves;
}

