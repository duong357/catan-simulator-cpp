#include "Piece.h"

Piece::Piece(Color c) : color(c)
{
}

Road::Road(Color c) : Piece(c)
{

}

Settlement::Settlement(Color c) : Piece(c)
{

}

City::City(Color c) : Settlement(c)
{
}

Robber::Robber() : Piece(Color())
{

}
