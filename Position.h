#ifndef _POSITION_H_
#define _POSITION_H_


struct position{
    int x;
    int y;

    bool operator==(const position& other) const {
        return (x == other.x && y == other.y);
    }
};

#endif