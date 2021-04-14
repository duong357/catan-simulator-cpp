//
// Created by heinz on 9/24/20.
//

#include "Corner.h"

bool Corner::isBottomCorner(int x, int y)
{
    return (x + y + 2) % 3 == 0;
}

bool Corner::isTopCorner(int x, int y)
{
    return (x + y - 2) % 3 == 0;
}

Corner::Corner(int x, int y) : Coordinate(x, y), house(nullptr)
{
    assert(isCorner(x,y));
}

void Corner::buildCity(Color color)
{
    *house = City(color);
}

void Corner::buildSettlement(Color color)
{
    *house = Settlement(color);
}

set<Tile> Corner::surroundingTiles()
{
    return set<Tile>();
}

ostream &operator<<(ostream &out, Corner &corner)
{
    cout << format();
    return out;
}
