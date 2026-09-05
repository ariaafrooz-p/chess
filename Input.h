#ifndef _INPUT_H_
#define _INPUT_H_
#include "Position.h"
#include "Board.h"
class Input{
    Board board{};
public:
    position cursor_pos{2,2};
    Input(){}
    Input(position p)
        : cursor_pos{p}{}
    position get_input_keyboard();
};

#endif