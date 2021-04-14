
#include "Tile.h"

Tile::Tile(Resource r, unsigned int number, char letter, int x, int y) : Coordinate(x, y), resource(r), number(number), letter(letter)
{
}
