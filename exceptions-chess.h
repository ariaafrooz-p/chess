#ifndef EXCEPTIONS_CHESS_H
#define EXCEPTIONS_CHESS_H

#include <stdexcept>
#include <string>

class IllegalMoveException : public std::exception {
    std::string message;
public:
    IllegalMoveException() : message("Illegal move attempted.") {}
    IllegalMoveException(const std::string& cause)
        : message("Illegal move attempted. Caused by: " + cause) {}
    ~IllegalMoveException() = default;
    virtual const char* what() const noexcept {
        return message.c_str();
    }
};

#endif