#ifndef CGRID_H
#define CGRID_H

#include <vector>



namespace Direction {
enum EDirection {
    Up = 0,
    UpRight = 1,
    Right = 2,
    DownRight = 3,
    Down,
    DownLeft,
    Left,
    UpLeft,
    _cnt,
};
const int map[_cnt][2] = {
    { 0, 1},
    { 1, 1},
    { 1, 0},
    { 1,-1},
    { 0,-1},
    {-1,-1},
    {-1, 0},
    {-1, 1},
};

inline EDirection reverse(EDirection dir) {
    return (EDirection) (((int)dir)^((int)_cnt));
};

inline EDirection turn(EDirection dir, int side) {
    int now = dir + side;
    now = now >= Direction::_cnt ? now - Direction::_cnt : now;
    return (EDirection) now;
};
}

struct SElement {
    enum ElementState {
        Free,
        Occupied,        
    };
    enum PathState {
        None = 0,
        InQueue = 1,
        NextInLine = 2,
        Checked = 3,
        InPath = 4,
    };
    int state;
    int neighbours[Direction::_cnt];
};

class CGrid {
private:
    std::vector< std::vector<SElement> > _grid;
    int _w, _h;
    
public:
    CGrid(int w, int h);
    
    /// Set state of grid element (basicaly color)
    void set(int x, int y, SElement::ElementState state);
    /// Set state of grid elements link (basicaly color)
    void link(int x, int y, Direction::EDirection direction, SElement::PathState state);
    
    void draw();
};

#endif //CGRID_H
