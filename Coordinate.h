#ifndef COORDINATE_H
#define COORDINATE_H
#include <iostream>
#include "GameException.h"
using namespace std;

enum class Direction
{
    N, NE, E, SE, S, SW, W, NW // clockwise starting from N
};

class Coordinate
{
public:
    static const unsigned int NUMBER_OF_SIDES = 6;
    Coordinate(int x, int y) : x(x), y(x) {}
    static bool isTile(int x, int y);
    static bool isCorner(int x, int y);
    static bool isAdjCorner(int x, int y);

#if 0
    bool isAdjCoordinate(int a, int b) const
    {
        if (isTile())
            throw GameException("in function isAdjTile(" + to_string(a) + "," + to_string(b) + "): argument denotes a tile instead of a corner");
        return dist(a, b, x, y) == 1 || (a - x == 1 && b - y == 1) || (a - x == -1 && b - y == -1);
    }
#endif
    vector<Coordinate> corners() const;
    vector<Coordinate> hexes() const // return array containing surrounding hexes of a corner (Priority: top->bottom, left->right) - DELETE WHAT THIS FUNCTION RETURNS
    {
        vector<Coordinate> temp;
        if (isTile())
            temp = {Coordinate(x+2, y+1), Coordinate(x+1, y+2), Coordinate(x-1, y+1), Coordinate(x-2, y-1), Coordinate(x-1, y-2), Coordinate(x+1, y-1)};
        if (isTopCorner())
            temp = {Coordinate(x+1,y), Coordinate(x,y+1), Coordinate(x-1,y-1)}; // NW, NE, S
        else if (isBottomCorner())
            temp = {Coordinate(x+1, y+1), Coordinate(x, y-1), Coordinate(x-1, y)}; // N, SW, SE
        return temp;
    }

#if 0
    Coordinate adjCorner(Direction d) const // returns corner iff Tile
    {
        if (isTile())
        {
            switch(d) // go clockwise starting with NW
            {
                case Direction::NW:
                    return Coordinate(x+1, y);
                case Direction::N:
                    return Coordinate(x+1, y+1);
                case Direction::NE:
                    return Coordinate(x, y+1);
                case Direction::SE:
                    return Coordinate(x-1, y);
                case Direction::S:
                    return Coordinate(x-1, y-1);
                case Direction::SW:
                    return Coordinate(x, y-1);
                default:
                    break;
            }
        }
        throw GameException("Function adjCorner(): Coordinate is not a tile!");
    }
    Coordinate adjTile(Direction d) const // returns TILE, regardless of whether corner or Tile
    {
        if (isTile())
            switch (d)
            {
                case Direction::NW:
                    return Coordinate(x+2, y+1);
                case Direction::NE:
                    return Coordinate(x+1, y+2);
                case Direction::W:
                    return Coordinate(x+1, y-1);
                case Direction::E:
                    return Coordinate(x-1, y+1);
                case Direction::SW:
                    return Coordinate(x-1, y-2);
                case Direction::SE:
                    return Coordinate(x-2, y-1);
                default:
                    break;
            }
        else if (isBottomCorner())
            switch (d)
            {
                case Direction::N:
                    return Coordinate(x+1, y+1);
                case Direction::SW:
                    return Coordinate(x, y-1);
                case Direction::SE:
                    return Coordinate(x-1, y);
                default:
                    break;
            }
        else if (isTopCorner())
            switch (d)
            {
                case Direction::S:
                    return Coordinate(x-1, y-1);
                case Direction::NW:
                    return Coordinate(x+1, y);
                case Direction::NE:
                    return Coordinate(x, y+1);
                default:
                    break;
            }
        throw GameException("Function adjTile(): no such hex or corner!)");
    }
#endif
    bool operator ==(Coordinate& h) const;
    friend ostream& operator <<(ostream& out, const Coordinate& h);
protected:
    int x, y;
};
#endif
