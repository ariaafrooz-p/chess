#include "Input.h"
#include "Position.h"
#include "Board.h"
#include <iostream>
#include <conio.h>   // Windows only

position Input::get_input_keyboard(){
    std::cout << "\033[" << cursor_pos.y << ";" << cursor_pos.x << "H";
    int c = _getch();
    if (c == 224 || c == 0) {           // arrow / special key prefix
        c = _getch();
        switch (c) {
            case 72:
                if(cursor_pos.y/2>1)
                    cursor_pos.y-=2; 
                break;
            case 80:
                if(cursor_pos.y/2<8)
                    cursor_pos.y+=2;
                break;
            case 75:
                if((cursor_pos.x+1)/3>1)
                    cursor_pos.x-=3;
                break;
            case 77:
                if((cursor_pos.x+1)/3<8)
                    cursor_pos.x+=3;
                break;
        }
        std::cout << "\033[" << cursor_pos.y << ";" << cursor_pos.x << "H";
    } else if (c == ' ') {              // space: 32, no prefix
        return{(cursor_pos.x+1)/3-1, cursor_pos.y/2-1};
    }
    return get_input_keyboard();
}