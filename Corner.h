//
// Created by heinz on 9/24/20.
//

#ifndef CATANSIMULATOR_CORNER_H
#define CATANSIMULATOR_CORNER_H
#include <cassert>
#include <set>
#include "Coordinate.h"
#include "Color.h"
#include "Tile.h"
#include "Piece.h"


class Corner : public Coordinate
{
public:
    Corner(int x, int y);
    static bool isTopCorner(int x, int y);
    static bool isBottomCorner(int x, int y);
    void buildCity(Color color);
    void buildSettlement(Color color);
    set<Tile> surroundingTiles();
    Settlement * house;
    friend ostream& operator <<(ostream& out, Corner& corner);
};

#endif //CATANSIMULATOR_CORNER_H
