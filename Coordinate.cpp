#include <vector>
#include "Coordinate.h"

bool Coordinate::isTile(int x, int y) // any coordinate that isn't a corner is a Tile
{
    return (x + y) % 3 == 0;
}

bool Coordinate::isAdjCorner(int x, int y) // if Coordinate, then return true if corner surrounds Coordinate; otherwise, return false
{
    if (isCorner(x, y))
        throw GameException("in function isAdjCorner(" + to_string(x) + "," + to_string(y) + "): argument denotes a corner instead of a tile");
    return dist(x, y, x, y) == 1 || (x - x == 1 && y - y == 1) || (x - x == -1 && y - y == -1);
}

#if 0
unsigned int Coordinate::dist(const Coordinate &h1, const Coordinate &h2) // NOTE: In this coordinate system, 'distance' is a measure of how many x or y movements it takes to go from point to point
{
    return (abs(h1.x - h2.x) + abs(h1.y - h2.y) + abs(h1.x + h1.y - h2.x - h2.y)) / 2;
}
#endif

bool Coordinate::isCorner(int x, int y) // any coordinate that isn't a Tile is a corner
{
    // return !isTile(x, y);
    return (x + y) % 3 != 0;
}

vector<Coordinate> Coordinate::corners() const // return array containing surrounding corners of a Coordinate (Priority: top-bottom, clockwise)
{
    vector<Coordinate> temp;
    if (isTopCorner())
        temp = {Coordinate(x+1, y+1), Coordinate(x-1, y), Coordinate(x, y-1)};
    else if (isBottomCorner())
        temp = {Coordinate(x+1, y), Coordinate(x, y+1), Coordinate(x-1, y-1)};
    else if (isTile())
        temp = {Coordinate(x+1,y),Coordinate(x+1,y+1),Coordinate(x, y+1),Coordinate(x-1,y),Coordinate(x-1,y-1),Coordinate(x,y-1)}; // NW, N, NE, SE, S, SW
    return temp;
}

bool Coordinate::operator==(Coordinate &h) const
{
    return x == h.x && y == h.y;
}

ostream &operator<<(ostream &out, const Coordinate &h)
{
    cout << "Coordinate:";
    if (h.isTile());
    else if (h.isTopCorner())
        cout << "TOP-Corner";
    else if (h.isBottomCorner())
        cout << "BOT-Corner";
    else // This case should never happen
        cout << "Unknown";
    cout << "(x=" << h.x << ",y=" << h.y << ")";
    return out;
}
