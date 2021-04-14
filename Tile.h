#ifndef TILE_H
#define TILE_H
#include <iostream>
#include "Coordinate.h"
#include "Resource.h"
using namespace std;

class Tile : public Coordinate
{
public:
    Tile(Resource r, unsigned int number, char letter, int x, int y);
#if 0
    Tile& operator=(const Tile& t)
		{
			x = t.x;
			y = t.y;
			resource = t.resource;
			number = t.number;
			return *this;
		}
		Tile(const Tile& t)
		{
			x = t.x;
			y = t.y;
			resource = t.resource;
			number = t.number;
		}
#endif
#if 0
    ~Tile()
		{
		}
#endif
    friend ostream& operator <<(ostream& out, Tile& t)
    {
        cout << "Tile(" << "x=" << t.x << ",y=" << t.y;
        if (t.resource != Resource::desert)
            cout << ",Letter=" << t.letter << ",Number=" << t.number;
        cout << ",Resource=" << t.resource;
        cout << ")\n";
        return out;
    }
private:
    Resource resource;
    Number number;
};
#endif
