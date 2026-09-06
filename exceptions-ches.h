#ifndef EXCEPTIONS_CHESS_H
#define EXCEPTIONS_CHESS_H

#include <stdexcept>

class IllegalMoveException : public std::exception {
public:
    const char* what() const noexcept override{
        return "Illegal move attempted.";
    }
};

#endif