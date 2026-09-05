#ifndef _PIECES_H_
#define _PIECES_H_
#include "Position.h"
#include <vector>
#include <string>

//♚ ♛ ♜ ♝ ♞ 

class Piece{
protected:
    std::string symbol=" ";
    std::string displaycolor="\033[33m";
    position pos{0,0};
public:
    bool has_just_moved_2_spaces{false};
    Piece()
        :displaycolor{"\033[0m"}, pos{0,0}{}
    Piece(position p)
        :pos{p}{}
    Piece(std::string d_color, position p)
        :pos{p}{
            if (d_color == "black") displaycolor="\033[34m";
            else if (d_color == "white")displaycolor="\033[0m";
            else displaycolor="\033[33m";
        }
    virtual ~Piece() = default;
    std::string get_symbol() const {return symbol;}
    std::string get_color() const {return displaycolor;}
    position get_position() const {return pos;}
    void set_position(position p) {pos = p;}
    std::string get_color_string() const {
        if (displaycolor == "\033[34m") return "black";
        else if (displaycolor == "\033[0m") return "white";
        else return "yellow";
    }
    
    virtual std::vector<position> determinemovement(const std::vector<std::vector<Piece *>> &board);
};

class Rook : virtual public Piece{
public:
    Rook()
        :Piece(){symbol="♜";}
    Rook(std::string d_color, position p)
        :Piece(d_color, p){symbol="♜";}
    virtual std::vector<position> determinemovement (const std::vector<std::vector<Piece *>> &board) override;
    
};

class Bishop : virtual public Piece{
public:
    Bishop()
        :Piece(){symbol="♝";}
    Bishop(std::string d_color, position p)
        :Piece(d_color, p){symbol="♝";}
    virtual std::vector<position> determinemovement (const std::vector<std::vector<Piece *>> &board) override;  
};

class Horse : public Piece{
public:
    Horse()
        :Piece(){symbol="♞";}
    Horse(std::string d_color, position p)
        :Piece(d_color, p){symbol="♞";}
    virtual std::vector<position> determinemovement (const std::vector<std::vector<Piece *>> &board) override;  
};

class Queen : public Rook, public Bishop{
public:
    Queen()
        :Piece(){symbol="♛";}
    Queen(std::string d_color, position p)
        :Piece(d_color, p){symbol="♛";}
    virtual std::vector<position> determinemovement (const std::vector<std::vector<Piece *>> &board) override;  
};

class King : public Piece{
public:
    King()
        :Piece(){symbol="♚";}
    King(std::string d_color, position p)
        :Piece(d_color, p){symbol="♚";}
    std::vector<position> illegal_moves_for_king (const std::vector<std::vector<Piece *>> &board);
    virtual std::vector<position> determinemovement (const std::vector<std::vector<Piece *>> &board) override;  
};

class Pawn : public Piece{
public:
    Pawn()
        :Piece(){symbol="♟"; has_just_moved_2_spaces=false;}
    Pawn(std::string d_color, position p)
        :Piece(d_color, p){symbol="♟";}
    virtual std::vector<position> determinemovement (const std::vector<std::vector<Piece *>> &board) override;  
};

#endif